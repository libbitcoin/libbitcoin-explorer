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
#include <sx/utility/coin.hpp>

#include <iostream>
#include <random>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/dispatch.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

namespace sx {

// TODO: reconcile with [data_chunk random_fill(size_t size)]
// Not testable due to lack of random engine injection.
ec_secret random_secret()
{
    std::random_device random;
    std::default_random_engine engine(random());

    ec_secret secret;
    for (uint8_t& byte: secret)
        byte = engine() % std::numeric_limits<uint8_t>::max();

    return secret;
}

// TODO: reconcile with [data_chunk random_secret()]
// Not testable due to lack of random engine injection.
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

bool read_addresses(std::vector<std::string> addresses, payaddr_list& payaddrs)
{
    for (const auto& address: addresses)
    {
        payment_address payaddr;
        if (!payaddr.set_encoded(address))
            return false;

        payaddrs.push_back(payaddr);
    }

    return true;
}

bool read_hard_index_args(int argc, const char* argv[], bool& is_hard,
    uint32_t& index)
{
    index = 0;
    is_hard = false;

    for (int i = 1; i < argc; ++i)
    {
        const std::string arg(argv[i]);
        if (is_option(arg, "hard" /*SX_OPTION_HARD*/))
            is_hard = true;

        else if (!parse(index, arg))
            return false;
    }

    return true;
}

bool read_public_of_private_key(ec_point& key, const std::string& arg,
    key_compression compression)
{
    bool compressed = true;
    auto secret = decode_hash(arg);
    if (secret == null_hash)
    {
        // Use the compression format of the key.
        compressed = libwallet::is_wif_compressed(arg);
        secret = libwallet::wif_to_secret(arg);
    }

    // Not a valid private key.
    if (secret == bc::null_hash)
        return false;

    // Override compression (to false), otherwise as imported or true.
    if (compression != key_compression::unspecified)
        compressed = (compression == key_compression::on);

    key = bc::secret_to_public_key(secret, compressed);
    return true;
}

bool validate_checksum(const data_chunk& data)
{
    if (data.size() < 5)
        return false;

    data_chunk rawdata(data.begin(), data.end() - 4);
    const auto bc_checksum = bitcoin_checksum(rawdata);

    data_chunk rawchecksum(data.end() - 4, data.end());
    const auto my_checksum = from_little_endian<uint32_t>(rawchecksum.begin());

    return bc_checksum == my_checksum;
}

} // sx
