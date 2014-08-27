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
#include "precompile.hpp"
#include <sx/command/help.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <sx/define.hpp>
#include <sx/display.hpp>
#include <sx/generated.hpp>

using namespace boost::program_options;
using namespace explorer;
using namespace explorer::commands;

// 100% coverage by line (as private to invoke())
static bool write_all_command_names(std::ostream& stream)
{
    const auto func = [&stream](std::shared_ptr<command> sx_command)
    {
        BITCOIN_ASSERT(sx_command != nullptr);
        stream << sx_command->name() << std::endl;
    };

    return broadcast(func);
}

// 100% coverage by line, loc ready.
console_result help::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& symbol = get_command_argument();

    // If there is no COMMAND then show usage for *this* command.
    if (symbol.empty())
    {
        write_usage(error);
        return console_result::failure;
    }

    // If the COMMAND is not a command, say so and list all commands.
    auto command = find(symbol);
    if (command == nullptr)
    {
        error << boost::format(SX_HELP_NOT_COMMAND) % symbol << std::endl;
        write_all_command_names(error);
        return console_result::failure;
    }

    // The COMMAND is valid so show its usage.
    command->write_usage(output);
    return console_result::okay;
}
