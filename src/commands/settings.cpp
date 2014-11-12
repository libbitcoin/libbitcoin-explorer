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
#include <map>
#include <bitcoin/explorer/prop_tree.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;
using namespace pt;

console_result settings::invoke(std::ostream& output, std::ostream& error)
{
    // bound parameters
    const auto& encoding = get_format_option();

    // TODO: load from metadata into settings list.
    // This must be updated for any settings metadata change.
    settings_list list;
    list.emplace("general.network", get_general_network_setting());
    list.emplace("general.retries", serialize(get_general_retries_setting()));
    list.emplace("general.wait", serialize(get_general_wait_setting()));
    list.emplace("mainnet.url", get_mainnet_url_setting());
    list.emplace("testnet.url", get_testnet_url_setting());

    write_stream(output, prop_tree(list), encoding);
    return console_result::okay;
}
