/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include <bitcoin/explorer/commands/help.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/generated.hpp>

using namespace boost::program_options;
using namespace bc::explorer;
using namespace bc::explorer::commands;

// 100% coverage by line (as private to invoke())
static bool write_all_command_names(std::ostream& stream)
{
    const auto func = [&stream](std::shared_ptr<command> explorer_command)
    {
        BITCOIN_ASSERT(explorer_command != nullptr);
        stream << explorer_command->name() << std::endl;
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
        write_usage(output);
        return console_result::okay;
    }

    // If the COMMAND is not a command, say so and list all commands.
    auto explorer_command = find(symbol);
    if (explorer_command == nullptr)
    {
        error << boost::format(BX_HELP_NOT_COMMAND) % symbol << std::endl;
        write_all_command_names(error);
        return console_result::failure;
    }

    // The COMMAND is valid so show its usage.
    explorer_command->write_usage(output);
    return console_result::okay;
}
