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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/command/hd-to-address.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result hd_to_address::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return console_result::failure;

    std::string encoded_key(get_arg_or_stream(argc, argv, std::cin));

    hd_public_key public_key;
    hd_private_key private_key;

    // NOTE: same idiom in hd_pub
    // First try loading private key and otherwise the public key.
    if (private_key.set_serialized(encoded_key))
        public_key = private_key;
    else if (!public_key.set_serialized(encoded_key))
    {
        std::cerr << "hd-pub: error reading key." << std::endl;
        return console_result::failure;
    }

    std::cout << public_key.address().encoded() << std::endl;
    return console_result::okay;
}

