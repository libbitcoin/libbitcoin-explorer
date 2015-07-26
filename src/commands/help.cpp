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

#include <bitcoin/explorer/commands/help.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/generated.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result help::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& symbol = get_command_argument();

    if (symbol.empty())
    {
        display_usage(output);
        return console_result::okay;
    }

    auto command = find(symbol);
    if (!command)
    {
        display_invalid_command(error, symbol);
        return console_result::failure;
    }

    command->load_options();
    command->load_arguments();
    command->write_help(output);
    return console_result::okay;
}
