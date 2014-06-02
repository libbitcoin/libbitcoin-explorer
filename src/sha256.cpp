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
#include <sx/command/sha256.hpp>
#include <sx/utility/console.hpp>

bool invoke(const int argc, const char* argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: sx sha256 DATA" << std::endl;
        return -1;
    }
    std::string arg;
    if (argc == 2)
        arg = argv[1];
    else
        arg = read_stream(std::cin);
    data_chunk data = decode_hex(arg);
    if (data.empty())
    {
        std::cerr << "sx: Non-hex input data." << std::endl;
        return -1;
    }
    std::cout << sha256_hash(data) << std::endl;
    return 0;
}

