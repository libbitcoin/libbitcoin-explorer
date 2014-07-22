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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/dispatch.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/compat.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

namespace sx {

// Not testable due to lack of random engine injection.
void random_secret(ec_secret& secret)
{
    data_chunk chunk(ec_secret_size);
    random_fill(chunk);
    std::copy(chunk.begin(), chunk.end(), secret.begin());
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
