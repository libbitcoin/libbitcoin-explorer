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
#pragma warning(push) 
#pragma warning(disable : 4996)
#include <sx/utility/console.hpp>

#include <iomanip>
#include <iostream>
#include <random>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#pragma warning(pop)

namespace sx {

//std::string get_filename(int argc, const char* argv[])
//{
//    return if_else(argc > 0, argv[0], SX_STDIN_PATH_SENTINEL);
//}

void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter)
{
    sentence = boost::join(words, delimiter);
}

std::string read_stream(std::istream& stream, bool trim)
{
    std::istreambuf_iterator<char> first(stream), last;
    std::string result(first, last);
    if (trim)
        boost::algorithm::trim(result);

    return result;
}

// Not testable due to lack of random engine injection.
void random_fill(bc::data_chunk& chunk)
{
    std::random_device random;
    std::default_random_engine engine(random());

    for (uint8_t& byte : chunk)
        byte = engine() % std::numeric_limits<uint8_t>::max();
}

// Not unit testable (sleep).
void sleep_ms(uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

void split(const std::string& sentence, std::vector<std::string>& words,
    const std::string& delimiter)
{
    boost::split(words, sentence, boost::is_any_of(delimiter));
}

// Not unit testable (process termination).
void terminate_process_on_error(const std::error_code& error)
{
    if (!error)
        return;

    bc::log_fatal() << error.message();
    exit(console_result::failure);
}

void trim_left(std::string& value, const std::string& chars)
{
    using namespace boost::algorithm;
    trim_left_if(value, is_any_of(chars));
}

} // sx