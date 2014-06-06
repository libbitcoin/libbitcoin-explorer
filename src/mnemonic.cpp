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
#include <wallet/wallet.hpp>
#include <sx/command/mnemonic.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

console_result mnemonic::invoke(int argc, const char* argv[])
{
    int mnemonic_size = 12;

    if (!validate_argument_range(argc, example(), 1, mnemonic_size))
        return console_result::failure;

    string_list words;

    if (argc > 1)
        get_args(argc, argv, words);
    else
        stream_to_words(std::cin, words);

    if (words.size() != 1 && words.size() != mnemonic_size)
    {
        line_out(std::cerr, explanation());
        return console_result::failure;
    }

    // $ echo "people blonde admit dart couple different truth common alas
    //   stumble time cookie" | sx mnemonic
    if (words.size() == mnemonic_size)
    {
        // Note that there is no dictionary validation in decode_mnemonic.
        std::cout << decode_mnemonic(words) << std::endl;
        return console_result::okay;
    }

    // $ echo foobar | sx mnemonic
    if (words.front().size() != deterministic_wallet::seed_size)
    {
        std::cerr << "sx: The seed must be exactly " <<
            deterministic_wallet::seed_size << " characters long."
            << std::endl;
        return console_result::failure;
    }

    // $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic
    std::string sentence;
    auto words_list = encode_mnemonic(words.front());
    join(words_list, sentence);
    std::cout << sentence << std::endl;
    return console_result::okay;
}

