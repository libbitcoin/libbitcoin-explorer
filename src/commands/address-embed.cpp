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

#include <bitcoin/explorer/commands/address-embed.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

#define ADDRESS_EMBED_SCRIPT "dup hash160 [ %1% ] equalverify checksig"

console_result address_embed::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& data = get_data_argument();
    const auto& version = get_version_option();

    // Create script from hash of data.
    auto tokens = format(ADDRESS_EMBED_SCRIPT) % base16(ripemd160_hash(data));
    const script embeded_script(split(tokens.str()));

    // Make ripemd hash of serialized script.
    const auto serialized_script = save_script(embeded_script);
    const auto ripemd160 = ripemd160_hash(serialized_script);

    // RECOMPILE REQUIRED FOR TESTNET
    const address pay_address(version, ripemd160);

    output << pay_address << std::endl;
    return console_result::okay;
}

//#!/bin/bash
//read INPUT
//DECODED_ADDR=$(echo $INPUT | sx ripemd160)
//SCRIPT=$(sx rawscript dup hash160 [ $DECODED_ADDR ] equalverify checksig)
//HASH=$(echo $SCRIPT | sx ripemd160)
//sx encode-addr $HASH
//
