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
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>

using namespace bc;
using namespace libwallet;

int display_help()
{
    puts("Usage:");
    puts("");
    puts("  mnemonic <<< \"[WORD1] [WORD2] ...\"");
    puts("  mnemonic <<< SEED");
    puts("");
    puts("Please email suggestions and questions to <genjix@riseup.net>.");
    return -1;
}

bool invoke(const int argc, const char* argv[])
{
    std::istreambuf_iterator<char> it(std::cin);
    std::istreambuf_iterator<char> end;
    std::string data(it, end);
    boost::algorithm::trim(data);
    string_list words;
    boost::split(words, data, boost::is_any_of("\n\t "));
    if (words.empty())
        return display_help();
    else if (words.size() == 1 &&
        words[0].size() == libwallet::deterministic_wallet::seed_size)
    {
        const std::string seed = words[0];
        string_list words = encode_mnemonic(seed);
        bool first = true;
        for (const std::string& word: words)
        {
            if (!first)
                std::cout << " ";
            std::cout << word;
            first = false;
        }
        std::cout << std::endl;
        return 0;
    }
    else
    {
        std::cout << decode_mnemonic(words) << std::endl;
        return 0;
    }
    // Should never happen!
    return 0;
}

