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
#include <iostream>
#include <string>
#include <sx/generated.hpp>
#include <sx/command/wallet.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>
#include <sx/utility/display.hpp>

namespace sx {

console_result dispatch_invoke(int argc, const char* argv[], 
    const std::string& alias)
{
    const auto target = (alias.empty() ? argv[0] : alias);
    const auto command = extensions::find(target);
    if (command == nullptr)
    {
        display_invalid_command(target);
        return console_result::failure;
    }

    return command->invoke(argc, argv);
}

bool dispatch_summary(const std::string& symbol)
{
    const auto command = extensions::find(symbol);
    if (command == nullptr)
    {
        display_invalid_command(symbol);
        return false;
    }

    return display_summary(command);
}

bool dispatch_usage()
{
    const auto func = [](std::shared_ptr<command> sx_command) -> void
    {
        display_usage(sx_command);
    };

    return extensions::broadcast(func);
}

console_result invoke(int argc, const char* argv[])
{
    // command line usage:
    // sx [-c|--config path] [[-h|--help|help command] | [command [args...]]]

    int position = 0;
    int last = argc - 1;

    // sx
    if (position == last)
    {
        display_usage();
        return console_result::okay;
    }

    // next token (skip process name)
    auto token = std::string(argv[++position]);

    // --config
    if (is_option(token, SX_OPTION_CONFIG))
    {
        if (position == last)
        {
            // sx -c|--config <missing path>
            display_usage();
            return console_result::failure;
        }

        // next token (skip -c|--config)
        token = argv[++position];

        if (!set_config_path(token))
        {
            display_invalid_config(token.c_str());
            return console_result::failure;
        }

        if (position == last)
            // sx -c|--config path
            // std::cerr << "Using config file: " << token << std::endl;
            return console_result::okay;

        // next token (skip path)
        // config option can be combined with help|command
        token = argv[++position];
    }

    // --help
    // The special case for "help" is actually an argument, not an option.
    if (is_option(token, SX_OPTION_HELP) || token == "help")
    {
        if (position == last)
            // sx [-c|--config path] -h|--help|help
            display_usage();
        else
        {
            // next token (skip -h|--help|help)
            token = argv[++position];

            // sx [-c|--config path] -h|--help|help command
            if (!dispatch_summary(token.c_str()))
                return console_result::failure;
        }

        // help option cannot be combined with command, ignore subsequent args
        return console_result::okay;
    }

    // invoke: always set the command as the first argument
    return dispatch_invoke(argc - position, &argv[position]);
}

} // sx