/*
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
#include "command_line.hpp"
#include "config.hpp"
#include "generated.hpp"
#include "commands/wallet.hpp"
#include "utility/console.hpp"
#include "utility/locale.hpp"

bool dispatch_invoke(const int argc, const char* argv[])
{
    auto symbol = std::string(argv[0]);
    auto command = find_command(symbol);

    if (command == nullptr)
    {
        display_invalid_command(symbol);
        return false;
    }

    return command->invoke(argc, argv);
}

bool dispatch_usage()
{
    auto func = [](std::shared_ptr<command> sx_command) -> void 
    {
        display_usage(sx_command);
    };

    return broadcast_command(func);
}

bool dispatch_usage(std::string& symbol)
{
    auto command = find_command(symbol);

    if (command == nullptr)
    {
        display_invalid_command(symbol);
        return false;
    }

    return display_usage(command);
}

bool display_usage(std::shared_ptr<command> command)
{
    // TODO: expand this presentation.
    std::cout << command->usage() << std::endl;
    return true;
}

int invoke(const int argc, const char* argv[])
{
    // command line usage:
    // sx [-c|--config path] [[-h|--help|help command] | [command [args...]]]

    int position = 0;
    const int last = argc - 1;

    // sx
    if (position == last)
    {
        display_usage();
        return main_success;
    }

    // next token (skip process name)
    auto token = std::string(argv[++position]);

    // --config
    if (token == "-c" || token == "--config")
    {
        if (position == last)
        {
            // sx -c|--config <missing path>
            display_usage();
            return main_failure;
        }

        // next token (skip -c|--config)
        token = std::string(argv[++position]);

        if (!set_config_path(token))
        {
            display_invalid_config(token);
            return main_failure;
        }

        if (position == last)
        {
            // sx -c|--config path
            // std::cerr << "Using config file: " << token << std::endl;
            return main_success;
        }

        // next token (skip path)
        // config option can be combined with help|command
        token = std::string(argv[++position]);
    }

    // --help
    if (token == "-h" || token == "--help" || token == "help")
    {
        if (position == last)
            // sx [-c|--config path] -h|--help|help
            display_usage();
        else
        {
            // next token (skip -h|--help|help)
            token = std::string(argv[++position]);

            // sx [-c|--config path] -h|--help|help command
            if (!dispatch_usage(token))
                return main_failure;
        }

        // help option cannot be combined with command, ignore subsequent args
        return main_success;
    }

    // invoke: always set the command as the first argument
    if (!dispatch_invoke(argc - position, &argv[position]))
        return main_failure;

    return main_success;
}