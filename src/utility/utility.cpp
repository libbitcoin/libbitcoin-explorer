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
// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without first testing it.
#include "precompile.hpp"
#pragma warning(push) 
#pragma warning(disable : 4996)
#include <sx/utility/utility.hpp>
#include <iomanip>
#include <iostream>
#include <random>
#include <signal.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#pragma warning(pop)
#include <sx/utility/callback_state.hpp>
#include <sx/utility/compat.hpp>

using namespace bc;
using namespace boost::posix_time;
using namespace libwallet;

namespace sx {
    
bool handle_error(callback_state& state, const std::error_code& code, 
    const std::string& format)
{
    if (code)
    {
        state.error(boost::format(format) % code.message());
        state.stop(console_result::failure);
        return false;
    }

    return true;
}

void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter)
{
    sentence = boost::join(words, delimiter);
}

// The key may be invalid, caller must test for null secret.
// Note that random fill of ec_secret could also generate an invalid key,
// but that would be less easily tested than this result.
ec_secret new_key(const bc::data_chunk& seed)
{
    // The testnet value is not relevant to the secret.
    constexpr bool testnet = false;

    // Using HD key generation because we don't yet have one for EC.
    const hd_private_key hd_key(seed, testnet);
    return hd_key.private_key();
}

// Not testable due to lack of random engine injection.
data_chunk new_seed(size_t bitlength)
{
    size_t fill_seed_size = bitlength / byte_size;
    data_chunk seed(fill_seed_size);
    random_fill(seed);
    return seed;
}

ptime now()
{
    using namespace boost::posix_time;
    ptime local_time_in_seconds(second_clock::local_time());
    return local_time_in_seconds;
}

// Not testable due to lack of random engine injection.
void random_fill(data_chunk& chunk)
{
    std::random_device random;
    std::default_random_engine engine(random());

    for (uint8_t& byte: chunk)
        byte = engine() % std::numeric_limits<uint8_t>::max();
}

std::string read_stream(std::istream& stream)
{
    SET_BINARY_FILE_MODE(true);
    std::istreambuf_iterator<char> first(stream), last;
    std::string result(first, last);
    SET_BINARY_FILE_MODE(false);
    return result;
}

// Not unit testable (sleep).
void sleep_ms(uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void split(const std::string& sentence, std::vector<std::string>& words,
    const std::string& delimiter)
{
    boost::split(words, sentence, boost::is_any_of(delimiter),
        boost::token_compress_on);
}

void trim(std::string& value)
{
    boost::trim(value);
}

void trim_left(std::string& value, const std::string& chars)
{
    boost::trim_left_if(value, boost::is_any_of(chars));
}

} // sx