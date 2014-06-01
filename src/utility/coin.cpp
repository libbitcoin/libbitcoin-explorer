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

void read_address_args(const int argc, const char* argv[], std::istream& cin,
    std::string& hex_str, uint8_t& version_byte)
{
    version_byte = 0;

    if (argc == 1)
    {
        // Two similar techniques for same arg requirements:

        // from encode_addr
        // hex_str = sx::read_stream(cin);

        // from wrap
        cin >> hex_str;
        int vb;
        cin >> vb;
        version_byte = vb;
    }
    else if (argc == 2)
    {
        if (strlen(argv[1]) > 5)
            hex_str = argv[1];
        else
        {
            sx::parse<uint8_t>(argv[1], version_byte);
            hex_str = sx::read_stream(cin);
        }
    }
    else if (argc == 3)
    {
        sx::parse<uint8_t>(argv[2], version_byte);
        hex_str = argv[1];
    }
}

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

    // compression override
    if (is_compressed != -1)
        compressed_flag = (is_compressed == 1);

    return secret != null_hash && key.set_secret(secret, compressed_flag);
}

bool read_public_or_private_key(elliptic_curve_key& key)
{
    auto arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    auto pubkey = decode_hex(arg);
    return key.set_public_key(pubkey);
}

bool validate_checksum(data_chunk& data)
{
    if (data.size() < 5)
        return false;

    data_chunk rawdata(data.begin(), data.end() - 4);
    auto bc_checksum = bitcoin_checksum(rawdata);

    data_chunk rawchecksum(data.end() - 4, data.end());
    auto my_checksum = from_little_endian<uint32_t>(rawchecksum.begin());

    return bc_checksum == my_checksum;
}

} // sx
