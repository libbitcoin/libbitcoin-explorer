/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result settings::invoke(std::ostream& output, std::ostream& error)
{
    const auto general_testnet = get_general_testnet_setting();
    const auto general_retries = get_general_retries_setting();
    const auto general_wait = get_general_wait_setting();
    const auto& server_url = get_server_url_setting();

    // TODO: generate this from configuration settings metadata at runtime,
    // and include localized descriptions rfom 
    output << format("general.retries = %1%") % general_retries << std::endl;
    output << format("general.testnet = %1%") % bool_to_string(general_testnet) << std::endl;
    output << format("general.wait = %1%") % general_wait << std::endl;
    output << format("server.url = %1%") % server_url << std::endl;

    return console_result::okay;
}