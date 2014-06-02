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
#include <sx/command/generated.hpp>
#include <sx/command/wallet.hpp>
#include <sx/utility/config.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>
#include <sx/utility/display.hpp>

namespace sx {

#define TAB1 3
#define TAB2 8
#define TAB3 35

bool dispatch_invoke(const int argc, const char* argv[], 
    const char* alias)
{
    auto target = (alias == nullptr ? argv[0] : alias);
    auto command = sx::extensions::find(target);
    if (command == nullptr)
    {
        display_invalid_command(target);
        return false;
    }
    return command->invoke(argc, argv);
}

bool dispatch_summary(const char* symbol)
{
    auto command = sx::extensions::find(symbol);
    if (command == nullptr)
    {
        display_invalid_command(symbol);
        return false;
    }
    return display_summary(command);
}

bool dispatch_usage()
{
    auto func = [](std::shared_ptr<command> sx_command) -> void 
    {
        display_usage(sx_command);
    };
    return sx::extensions::broadcast(func);
}

bool display_summary(std::shared_ptr<command> command)
{
    auto inset = (std::string(TAB1, ' ') + command->name());
    line_out(std::cout, command->category());
    line_out(std::cout, command->subcategory(), TAB2);
    line_out(std::cout, command->description(), TAB3, inset.c_str());
    return true;
}

bool display_usage(std::shared_ptr<command> command)
{
    line_out(std::cout, command->example());
    line_out(std::cout, command->explanation());
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
    if (is_option(token, SX_OPTION_CONFIG))
    {
        if (position == last)
        {
            // sx -c|--config <missing path>
            display_usage();
            return main_failure;
        }

        // next token (skip -c|--config)
        token = argv[++position];

        if (!set_config_path(token))
        {
            display_invalid_config(token.c_str());
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
        token = argv[++position];
    }

    // --help
    // The special case for "help" is retained for compatibility.
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

} // sx