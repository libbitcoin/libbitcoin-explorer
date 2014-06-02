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
#include <bitcoin/bitcoin.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool sx::extensions::unwrap::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    std::string hex_str(get_arg_or_stream(argc, argv, std::cin));
    data_chunk bytes = decode_hex(hex_str);

    if (bytes.size() < 5)
    {
        std::cerr << "Error: Must be at least five bytes" << std::endl;
        return false;
    }

    if (!validate_checksum(bytes))
    {
        std::cerr << "Error: checksum does not match" << std::endl;
        return false;
    }

    data_chunk rawdata(bytes.begin(), bytes.end() - 4);
    data_chunk output(rawdata.begin() + 1, rawdata.end());
    int version_byte = rawdata.front();

    std::cout << output << " " << version_byte << std::endl;
    return true;
}
