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
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    std::string hex_str;
    if (argc == 1) {
        hex_str = read_stdin();
    }
    else if (argc == 2) 
    {
        hex_str = argv[1];
    }
    data_chunk bytes = decode_hex(hex_str);
    if (bytes.size() < 5) {
        std::cerr << "Error: Must be at least five bytes" << std::endl;
        return -1;
    }
    data_chunk rawdata(bytes.begin(), bytes.end() - 4);
    data_chunk rawchecksum(bytes.end() - 4, bytes.end());
    uint32_t checksum = bitcoin_checksum(rawdata);
    uint32_t my_checksum = from_little_endian<uint32_t>(rawchecksum.begin());
    if (checksum != my_checksum) {
        std::cerr << "Error: checksum does not match" << std::endl;
        return -1;
    }
    int vbyte = rawdata[0];
    data_chunk output(rawdata.begin()+1, rawdata.end());
    std::cout << output << " " << vbyte << std::endl;
    return 0;
}
