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
#include <sx/command/decode-addr.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result decode_addr::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    std::string addr_str(get_arg_or_stream(argc, argv, std::cin));

    payment_address addr;
    if (!addr.set_encoded(addr_str))
    {
        std::cerr << "decode-addr: Bad address '" << addr_str << "'."
            << std::endl;
        return console_result::failure;
    }

    std::cout << addr.hash() << std::endl;
    return console_result::okay;
}

