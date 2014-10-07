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

#include <bitcoin/explorer/display.hpp>

#include <iostream>
#include <boost/format.hpp>
#include <bitcoin/explorer/dispatch.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

namespace libbitcoin {
namespace explorer {

void display_command_names(std::ostream& stream)
{
    const auto func = [&stream](std::shared_ptr<command> explorer_command)
    {
        BITCOIN_ASSERT(explorer_command != nullptr);
        stream << format(BX_LISTED_COMMAND_NAME) % explorer_command->name() << std::endl;
    };

    broadcast(func);
}

void display_invalid_command(std::ostream& stream, const std::string& command)
{
    stream << format(BX_INVALID_COMMAND) % command << std::endl;
}

void display_invalid_parameter(std::ostream& stream, 
    const std::string& message)
{
    stream << format(BX_INVALID_PARAMETER) % message << std::endl;
}

void display_usage(std::ostream& stream)
{
    stream << "Using bx: " << std::endl;
    stream << std::endl;
    stream << "  bx COMMAND [...]" << std::endl;
    stream << std::endl;
    stream << "  -c, --config          Specify a config file for the command" << std::endl;
    stream << "  -h, --help            Get a description of the command" << std::endl;
    stream << std::endl;
    stream << "The bx commands are:" << std::endl;
    stream << std::endl;

    display_command_names(stream);

    stream << std::endl;
    stream << "For help on a specific command: " << std::endl;
    stream << std::endl;
    stream << "  bx help COMMAND" << std::endl;
    stream << std::endl;
    stream << "Bitcoin Explorer home page: " << std::endl;
    stream << std::endl;
    stream << "  https://github.com/libbitcoin/libbitcoin_explorer" << std::endl;
}

} // namespace explorer
} // namespace libbitcoin
