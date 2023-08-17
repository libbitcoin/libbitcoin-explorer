/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/config/dictionary.hpp>

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace po;

// DRY
static const std::string language_en = "en";
static const std::string language_es = "es";
static const std::string language_ja = "ja";
static const std::string language_zh_Hans = "zh_Hans";

dictionary::dictionary()
  : value_(&wallet::language::electrum::en)
{
}

dictionary::dictionary(const std::string& token)
  : dictionary()
{
    std::stringstream(token) >> *this;
}

dictionary::dictionary(const wallet::dictionary& dictionary)
  : value_(&dictionary)
{
}

dictionary::dictionary(const dictionary& other)
  : value_(other.value_)
{
}

dictionary::operator const wallet::dictionary&() const
{
    return *value_;
}

std::istream& operator>>(std::istream& input, dictionary& argument)
{
    std::string token;
    input >> token;

    if (token == language_en)
        argument.value_ = &wallet::language::electrum::en;
    else if (token == language_es)
        argument.value_ = &wallet::language::electrum::es;
    else if (token == language_ja)
        argument.value_ = &wallet::language::electrum::ja;
    else if (token == language_zh_Hans)
        argument.value_ = &wallet::language::electrum::zh_Hans;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(token));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const dictionary& argument)
{
    std::string text;

    if (argument.value_ == &bc::wallet::language::en)
        text = language_en;
    else if (argument.value_ == &bc::wallet::language::es)
        text = language_es;
    else if (argument.value_ == &bc::wallet::language::ja)
        text = language_ja;
    else if (argument.value_ == &bc::wallet::language::zh_Hans)
        text = language_zh_Hans;
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected language value.");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
