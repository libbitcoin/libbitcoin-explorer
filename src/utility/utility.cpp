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
#include <sx/utility/utility.hpp>
#ifdef _MSC_VER
#include <fcntl.h>
#include <io.h>
#include <stdio.h>
#endif
#include <iomanip>
#include <iostream>
#include <random>
#include <stdint.h>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <bitcoin/bitcoin.hpp>
#pragma warning(pop)

namespace sx {

void join(const std::vector<std::string>& words, std::string& sentence,
    const std::string& delimiter)
{
    sentence = boost::join(words, delimiter);
}

boost::posix_time::ptime now()
{
    using namespace boost::posix_time;
    ptime local_time_in_seconds(second_clock::local_time());
    return local_time_in_seconds;
}

// Not testable due to lack of random engine injection.
void random_fill(bc::data_chunk& chunk)
{
    std::random_device random;
    std::default_random_engine engine(random());

    for (uint8_t& byte: chunk)
        byte = engine() % std::numeric_limits<uint8_t>::max();
}

// Not testable due to lack of random engine injection.
void random_secret(bc::ec_secret& secret)
{
    bc::data_chunk chunk(bc::ec_secret_size);
    random_fill(chunk);
    std::copy(chunk.begin(), chunk.end(), secret.begin());
}

std::string read_stream(std::istream& stream)
{
#ifdef _MSC_VER
    // The function sets the _fmode global variable.
    // This specifies the default translation mode for 
    // file I/O operations 
    _setmode(_fileno(stdin), _O_BINARY);
#endif

    std::istreambuf_iterator<char> first(stream), last;
    std::string result(first, last);

#ifdef _MSC_VER
    // The default setting of _fmode is _O_TEXT.
    // msdn.microsoft.com/en-us/library/61dstksf.aspx
    _setmode(_fileno(stdin), _O_TEXT);
#endif

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
    boost::split(words, sentence, boost::is_any_of(delimiter));
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