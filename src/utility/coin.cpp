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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

namespace sx {

// TODO: move to consumer and emit when this is false.
// std::cerr << "Invalid private key." << std::endl;
bool read_private_key(elliptic_curve_key& key, int is_compressed)
{
    return read_private_key(key, read_stdin(), is_compressed);
}

bool read_private_key(elliptic_curve_key& key, const std::string& arg,
    int is_compressed)
{
    bool compressed_flag = true;
    auto secret = decode_hash(arg);
    if (secret == null_hash)
    {
        secret = libwallet::wif_to_secret(arg);
        compressed_flag = libwallet::is_wif_compressed(arg);
    }

    // Overrides for compression
    if (is_compressed == 0)
        compressed_flag = false;
    else if (is_compressed == 1)
        compressed_flag = true;

    return secret != null_hash && key.set_secret(secret, compressed_flag);
}

// TODO: move to consumer and emit when this is false.
// std::cerr << "Invalid public or private key." << std::endl;
bool read_public_or_private_key(elliptic_curve_key& key)
{
    auto arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    auto pubkey = decode_hex(arg);
    return key.set_public_key(pubkey);
}

} // sx
