/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#include <bitcoin/explorer/primitives/language.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// DRY
static const char* language_en = "en";
static const char* language_es = "es";
static const char* language_ja = "ja";
static const char* language_zh_Hans = "zh_Hans";
static const char* language_zh_Hant = "zh_Hant";

language::language()
    : language(bip39::language::unknown)
{
}

language::language(const std::string& token)
{
    std::stringstream(token) >> *this;
}

language::language(bip39::language language)
    : value_(language)
{
}

language::language(const language& other)
    : language(other.value_)
{
}

language::operator bip39::language() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, language& argument)
{
    std::string text;
    input >> text;

    if (text == language_en)
        argument.value_ = bip39::language::en;
    else if (text == language_es)
        argument.value_ = bip39::language::es;
    else if (text == language_ja)
        argument.value_ = bip39::language::ja;
    else if (text == language_zh_Hans)
        argument.value_ = bip39::language::zh_Hans;
    else if (text == language_zh_Hant)
        argument.value_ = bip39::language::zh_Hant;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const language& argument)
{
    std::string value;

    switch (argument.value_)
    {
        case bip39::language::en:
            value = language_en;
            break;
        case bip39::language::es:
            value = language_es;
            break;
        case bip39::language::ja:
            value = language_ja;
            break;
        case bip39::language::zh_Hans:
            value = language_zh_Hans;
            break;
        case bip39::language::zh_Hant:
            value = language_zh_Hant;
            break;
        default:
            BITCOIN_ASSERT_MSG(false, "Unexpected encoding value.");
    }

    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
