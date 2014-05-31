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
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;
using namespace libwallet;

std::string read_data()
{
    std::istreambuf_iterator<char> it(std::cin);
    std::istreambuf_iterator<char> end;
    return std::string(it, end);
}

bool invoke(const int argc, const char* argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "Usage: genaddr N [CHANGE]" << std::endl;
        return -1;
    }
    size_t n;
    try
    {
        n = boost::lexical_cast<size_t>(argv[1]);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "genaddr: Bad N provided" << std::endl;
        return -1;
    }
    bool for_change = false;
    if (argc == 3)
    {
        std::string change_str = argv[2];
        boost::algorithm::to_lower(change_str);
        if (change_str == "true" || change_str == "1")
            for_change = true;
    }
    libwallet::deterministic_wallet wallet;
    std::string user_data = read_data();
    if (!wallet.set_seed(user_data))
    {
        data_chunk mpk = decode_hex(user_data);
        if (!wallet.set_master_public_key(mpk))
        {
            std::cerr << "genaddr: No valid master public key, or "
                << "private secret key was passed in." << std::endl;
            return -1;
        }
    }
    data_chunk pubkey = wallet.generate_public_key(n, for_change);
    payment_address addr;
    set_public_key(addr, pubkey);
    std::cout << addr.encoded() << std::endl;
    return 0;
}

