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
#include "precompile.hpp"
#include <bitcoin/explorer/commands/address-embed.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result address_embed::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto& data = get_file_argument();

    error << BX_ADDRESS_EMBED_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/bin/bash
//read INPUT
//DECODED_ADDR=$(echo $INPUT | sx ripemd160)
//SCRIPT=$(sx rawscript dup hash160 [ $DECODED_ADDR ] equalverify checksig)
//HASH=$(echo $SCRIPT | sx ripemd160)
//sx encode-addr $HASH
//
