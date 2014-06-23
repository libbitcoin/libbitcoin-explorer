/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <fstream>
#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <sx/generated.hpp>
#include <sx/dispatch.hpp>
#include <sx/display.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/environment.hpp>

using namespace po;
using namespace boost::filesystem;

namespace sx {

console_result dispatch(int argc, const char* argv[])
{
    if (argc == 1)
    {
        display_usage();
        return console_result::okay;
    }

    return dispatch_invoke(argc - 1, &argv[1]);
}

// Not unit testable (reliance on untestable functions and embeded io).
console_result dispatch_invoke(int argc, const char* argv[])
{
    const std::string target(argv[0]);
    const auto command = find(target);
    if (command == nullptr)
    {
        display_invalid_command(target);
        return console_result::failure;
    }

    std::string message;
    variables_map variables;
    if (!load_variables(variables, message, *command, std::cin, argc, argv))
    {
        display_invalid_variables(message);
        return console_result::failure;
    }

    // Injection of io streams allows for test.
    return command->invoke(std::cin, std::cout, std::cerr);
}

// TODO: Update using program_options presentation.
bool dispatch_usage()
{
    const auto func = [](std::shared_ptr<command> sx_command) -> void
    {
        display_usage(sx_command);
        display_line();
    };

    return broadcast(func);
}

path get_config_variable(variables_map& variables)
{
    // Read config from the map so we don't require an early notify call.
    const auto config = variables[SX_VARIABLE_CONFIG];

    // prevent exception in the case where the config variable is not set.
    return if_else(config.empty(), path(), config.as<path>());
}

void load_command_variables(variables_map& variables, command& instance,
    std::istream& input, int argc, const char* argv[]) throw()
{
    // command metadata is preserved on members for later usage presentation
    auto options = instance.load_options();
    auto arguments = instance.load_arguments();

    // parse inputs
    auto command_parser = command_line_parser(argc, argv).options(options)
        .positional(arguments);

    // map parsed inputs into variables map
    store(command_parser.run(), variables);

    // For variables with STDIN fallback load the input stream as necessary.
    instance.load_stream(input, variables);
}

// Not unit testable (without creating actual config files).
void load_configuration_variables(variables_map& variables, command& instance)
    throw()
{
    const auto config_path = get_config_variable(variables);
    if (config_path.empty())
        return;

    options_description config_settings("settings");
    instance.load_settings(config_settings);

    // does not throw on missing file, would have to test existence
    std::ifstream file(config_path.generic_string());

    // parse inputs
    auto configuration = parse_config_file(file, config_settings);

    // map parsed inputs into variables map
    store(configuration, variables);
}

// Not unit testable (reliance on shared test process environment).
void load_environment_variables(variables_map& variables, command& instance)
    throw()
{
    options_description environment_variables("environment");
    instance.load_environment(environment_variables);

    // parse inputs
    auto environment = parse_environment(environment_variables,
        SX_ENVIRONMENT_VARIABLE_PREFIX);

    store(environment, variables);
}

// Not unit testable (reliance on untestable functions).
bool load_variables(variables_map& variables, std::string& message,
    command& instance, std::istream& input, int argc, const char* argv[])
{
    try
    {
        // Command must store before environment in order for commands to supercede.
        load_command_variables(variables, instance, input, argc, argv);

        // Environment must store before configuration in order to specify the path.
        load_environment_variables(variables, instance);

        // Configuration is lowest priority, which will cause confusion if there is
        // composition between them, which therefore should be avoided.
        load_configuration_variables(variables, instance);

        // Send notifications and update bound variables.
        notify(variables);
    }
    catch (const po::error& e)
    {
        message = e.what();
        return false;
    }

    return true;
}

} // sx
