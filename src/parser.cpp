/**
 * Copyright (c) 2011-2018 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/parser.hpp>

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/system.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace boost::system;

namespace libbitcoin {
namespace explorer {

parser::parser(command& instance)
  : help_(false), instance_(instance)
{
}

bool parser::help() const
{
    return help_;
}

system::options_metadata parser::load_options()
{
    return instance_.load_options();
}

system::arguments_metadata parser::load_arguments()
{
    return instance_.load_arguments();
}

system::options_metadata parser::load_settings()
{
    system::options_metadata settings("settings");
    instance_.load_settings(settings);
    return settings;
}

system::options_metadata parser::load_environment()
{
    system::options_metadata environment("environment");
    instance_.load_environment(environment);
    return environment;
}

void parser::load_command_variables(variables_map& variables,
    std::istream& input, int argc, const char* argv[])
{
    system::config::parser::load_command_variables(variables, argc, argv);

    // Don't load rest if help is specified.
    // For variable with stdin or file fallback load the input stream.
    if (!get_option(variables, BX_HELP_VARIABLE))
        instance_.load_fallbacks(input, variables);
}

bool parser::parse(std::string& out_error, std::istream& input,
    int argc, const char* argv[])
{
    try
    {
        variables_map variables;

        // Must store before environment in order for commands to supercede.
        load_command_variables(variables, input, argc, argv);

        // Don't load rest if help is specified.
        if (!get_option(variables, BX_HELP_VARIABLE))
        {
            // Must store before configuration in order to specify the path.
            load_environment_variables(variables,
                BX_ENVIRONMENT_VARIABLE_PREFIX);

            // Is lowest priority, which will cause confusion if there is
            // composition between them, which therefore should be avoided.
            /* auto file = */ load_configuration_variables(variables,
                BX_CONFIG_VARIABLE);

            // Set variable defaults, send notifications and update bound vars.
            notify(variables);

            // Set the instance defaults from config values.
            instance_.set_defaults_from_config(variables);
        }
        else
        {
            help_ = true;
        }
    }
    catch (const po::error& e)
    {
        // This is obtained from boost, which circumvents our localization.
        out_error = e.what();
        return false;
    }

    return true;
}

} // namespace explorer
} // namespace libbitcoin
