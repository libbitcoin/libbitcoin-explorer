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
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/command/mnemonic.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace libwallet;

// Read all args to a string list in order.
void args_to_words(const int argc, const char* argv[], string_list& words)
{
    for (int i = 1; i < argc; ++i)
        words.push_back(argv[i]);
}

// Read STDIN to a string list in order.
void stdin_to_words(string_list& words)
{
    std::string data(sx::read_stdin(true));
    ////////boost::split(words, data, boost::is_any_of("\n\t "));
}

bool sx::extensions::mnemonic::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 12))
        return false;

    string_list in_words;

    if (argc == 1)
        stdin_to_words(in_words);
    else
        args_to_words(argc, argv, in_words);

    if (in_words.size() != 1 && in_words.size() != 12)
    {
        line_out(std::cerr, explanation());
        return false;
    }

    // $ echo "people blonde admit dart couple different truth common alas
    //   stumble time cookie" | sx mnemonic
    if (in_words.size() == 12)
    {
        // Note that there is no dictionary validation in decode_mnemonic.
        std::cout << decode_mnemonic(in_words) << std::endl;
        return true;
    }

    // $ echo foobar | sx mnemonic
    if (in_words[0].size() != deterministic_wallet::seed_size)
    {
        std::cerr << "sx: The seed must be exactly " <<
            deterministic_wallet::seed_size << " characters long."
            << std::endl;
        return false;
    }

    // $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic
    string_list out_words = encode_mnemonic(in_words[0]);
    //////std::string sentence = boost::join(out_words, " ");
    //////std::cout << sentence << std::endl;
    return true;
}

