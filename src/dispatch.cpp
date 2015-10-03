/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include <bitcoin/explorer/dispatch.hpp>

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/throw_exception.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/utility.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace boost::system;

namespace libbitcoin {
namespace explorer {

// Not unit testable (reliance on untestable function).
console_result dispatch(int argc, const char* argv[], 
    std::istream& input, std::ostream& output, std::ostream& error)
{
    if (argc == 1)
    {
        display_usage(output);
        return console_result::okay;
    }

    return dispatch_invoke(argc - 1, &argv[1], input, output, error);
}

// Swap Unicode input stream for binary stream in Windows builds.
static std::istream& get_command_input(command& command, std::istream& input)
{
#ifdef _MSC_VER
    if (command.requires_raw_input())
    {
        bc::set_binary_stdin();
        return std::cin;
    }

    bc::set_utf8_stdin();
#endif

    return input;
}

// Swap Unicode output stream for binary stream in Windows builds.
static std::ostream& get_command_output(command& command, std::ostream& output)
{
#ifdef _MSC_VER
    if (command.requires_raw_output())
    {
        bc::set_binary_stdout();
        return std::cout;
    }

    bc::set_utf8_stdout();
#endif

    return output;
}

// Set Unicode error stream in Windows builds.
static std::ostream& get_command_error(command& command, std::ostream& error)
{
    bc::set_utf8_stderr();
    return error;
}

// Not unit testable (reliance on untestable functions).
console_result dispatch_invoke(int argc, const char* argv[],
    std::istream& input, std::ostream& output, std::ostream& error)
{
    const std::string target(argv[0]);
    const auto command = find(target);

    if (!command)
    {
        const std::string superseding(formerly(target));
        display_invalid_command(error, target, superseding);
        return console_result::failure;
    }

    std::string message;
    variables_map variables;

    auto& in = get_command_input(*command, input);
    if (!load_variables(variables, message, *command, in, argc, argv))
    {
        display_invalid_parameter(error, message);
        return console_result::failure;
    }

    if (get_help_option(variables))
    {
        command->write_help(output);
        return console_result::okay;
    }

    auto& err = get_command_error(*command, error);
    auto& out = get_command_output(*command, output);
    return command->invoke(out, err);
}

path get_config_option(variables_map& variables)
{
    // Read config from the map so we don't require an early notify call.
    const auto& config = variables[BX_CONFIG_VARIABLE];

    // prevent exception in the case where the config variable is not set.
    if (config.empty())
        return path();

    return config.as<path>();
}

bool get_help_option(variables_map& variables)
{
    // Read help from the map so we don't require an early notify call.
    const auto& help = variables[BX_HELP_VARIABLE];

    // prevent exception in the case where the help variable is not set.
    if (help.empty())
        return false;

    return help.as<bool>();
}

void load_command_variables(variables_map& variables, command& instance,
    std::istream& input, int argc, const char* argv[])
{
    // commands metadata is preserved on members for later usage presentation
    const auto& options = instance.load_options();
    const auto& arguments = instance.load_arguments();

    auto command_parser = command_line_parser(argc, argv).options(options)
        .allow_unregistered().positional(arguments);
    store(command_parser.run(), variables);

    // Don't load rest if help is specified.
    // For variable with stdin or file fallback load the input stream.
    if (!get_help_option(variables))
        instance.load_fallbacks(input, variables);
}

void load_configuration_variables(variables_map& variables, command& instance)
{
    options_description config_settings("settings");
    instance.load_settings(config_settings);
    const auto config_path = get_config_option(variables);

    // If the existence test errors out we pretend there's no file :/.
    error_code code;
    if (!config_path.empty() && exists(config_path, code))
    {
        const auto& path = config_path.string();

        std::ifstream file(path, std::ios::binary);
        if (!file.good())
        {
            BOOST_THROW_EXCEPTION(reading_file(path.c_str()));
        }

        const auto configuration = parse_config_file(file, config_settings);
        store(configuration, variables);
        return;
    }

    // loading from an empty stream causes the defaults to populate.
    std::stringstream stream;
    const auto configuration = parse_config_file(stream, config_settings);
    store(configuration, variables);
}

void load_environment_variables(variables_map& variables, command& instance)
{
    options_description environment_variables("environment");
    instance.load_environment(environment_variables);
    const auto environment = parse_environment(environment_variables,
        BX_ENVIRONMENT_VARIABLE_PREFIX);
    store(environment, variables);
}

void set_variable_values(variables_map& variables, command& instance)
{
    notify(variables);
    instance.set_defaults_from_config(variables);
}

bool load_variables(variables_map& variables, std::string& message,
    command& instance, std::istream& input, int argc, const char* argv[])
{
    try
    {
        // Must store before environment in order for commands to supercede.
        load_command_variables(variables, instance, input, argc, argv);

        // Don't load rest if help is specified.
        if (!get_help_option(variables))
        {
            // Must store before configuration in order to specify the path.
            load_environment_variables(variables, instance);

            // Is lowest priority, which will cause confusion if there is
            // composition between them, which therefore should be avoided.
            load_configuration_variables(variables, instance);

            // Set defaults, send notifications and update bound variables.
            set_variable_values(variables, instance);
        }
    }
    catch (const po::error& e)
    {
        // This is obtained from boost, which circumvents our localization.
        message = e.what();
        return false;
    }

    return true;
}

} // namespace explorer
} // namespace libbitcoin
