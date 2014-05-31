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
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc > 3)
    {
        std::cerr << "Usage: sx encode-addr HASH [VERSION] " << std::endl;
        return -1;
    }

    std::string addr_str;
    uint8_t version_byte = 0;

    if (argc == 1)
    {
        addr_str = read_stdin();
    }
    else if (argc == 2)
    {
        if (strlen(argv[1]) > 5)
            addr_str = argv[1];
        else
        {
            version_byte = boost::lexical_cast<uint32_t>(argv[1]);
            addr_str = read_stdin();
        }
    }
    else
    {
        BITCOIN_ASSERT(argc == 3);
        version_byte = boost::lexical_cast<uint32_t>(argv[2]);
        addr_str = argv[1];
    }

    short_hash hashdata = decode_short_hash(addr_str);
    if (hashdata == null_short_hash)
    {
        std::cerr << "Incorrect HASH passed in." << std::endl;
        return -1;
    }

    payment_address addr(version_byte, hashdata);
    std::cout << addr.encoded() << std::endl;
    return 0;
}
