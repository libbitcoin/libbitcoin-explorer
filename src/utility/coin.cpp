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
#include <iostream>
#include <random>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;

namespace sx {

data_chunk random_fill(size_t size)
{
    std::random_device device;
    std::default_random_engine engine(device());

    std::uniform_int_distribution<min_uniform_dist_size>
        distribution(0, std::numeric_limits<min_uniform_dist_size>::max());

    data_chunk result;
    for (size_t i = 0; i < size; ++i)
        result.push_back(static_cast<uint8_t>(distribution(engine)));

    return result;
}

bool read_address_tuple(const int argc, const char* argv[], 
    std::istream& stream, std::string& hex_str, uint8_t& version_byte)
{
    version_byte = 0;

    if (argc == 1)
    {
        // Two similar techniques for same arg requirements:

        // from encode_addr
        hex_str = sx::read_stream(stream);

        // from wrap
        //stream >> hex_str;
        //int vb;
        //stream >> vb;
        //version_byte = vb;
    }
    else if (argc == 2)
    {
        const std::string arg(argv[1]);
        if (arg.length() > 5)
            hex_str = arg;
        else
        {
            if (!sx::parse<uint8_t>(argv[1], version_byte))
                return false;
            hex_str = sx::read_stream(stream);
        }
    }
    else if (argc == 3)
    {
        if (!sx::parse<uint8_t>(argv[2], version_byte))
            return false;
        hex_str = argv[1];
    }

    return true;
}

bool read_addresses(const int argc, const char* argv[], 
    payaddr_list& payaddrs)
{
    for (int i = 1; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (sx::is_option(arg))
            continue;
        payment_address payaddr;
        if (!payaddr.set_encoded(arg))
            return false;
        payaddrs.push_back(payaddr);
    }
    return true;
}

bool read_hard_index_args(const int argc, const char* argv[], bool& is_hard,
    uint32_t& index)
{
    index = 0;
    is_hard = false;

    for (int i = 1; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (sx::is_option(arg, SX_OPTION_HARD))
            is_hard = true;
        else if (!sx::parse<uint32_t>(arg, index))
            return false;
    }

    return true;
}

bool read_private_key(elliptic_curve_key& key, std::istream& stream,
    key_compression is_compressed)
{
    return read_private_key(key, read_stream(stream), is_compressed);
}

bool read_private_key(elliptic_curve_key& key, const std::string& arg,
    key_compression is_compressed)
{
    bool compressed_flag = true;
    auto secret = decode_hash(arg);
    if (secret == null_hash)
    {
        // Both compression and uncompression options are necessary because
        // the default in this case is to accept the format of the key.
        secret = libwallet::wif_to_secret(arg);
        compressed_flag = libwallet::is_wif_compressed(arg);
    }

    if (secret == null_hash)
        return false;

    if (is_compressed != key_compression::unspecified)
        compressed_flag = (is_compressed == key_compression::on);

    return key.set_secret(secret, compressed_flag);
}

bool read_public_or_private_key(elliptic_curve_key& key, std::istream& stream)
{
    auto arg = read_stream(stream);
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
