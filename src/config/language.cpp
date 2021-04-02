/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/config/language.hpp>

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
static const std::string language_fr = "fr";
static const std::string language_it = "it";
static const std::string language_cs = "cs";
static const std::string language_pt = "pt";
static const std::string language_ja = "ja";
static const std::string language_ko = "ko";
static const std::string language_zh_Hans = "zh_Hans";
static const std::string language_zh_Hant = "zh_Hant";

language::language()
  : value_(&wallet::language::en)
{
}

language::language(const std::string& token)
  : language()
{
    std::stringstream(token) >> *this;
}

language::language(const wallet::dictionary& language)
  : value_(&language)
{
}

language::language(const language& other)
  : value_(other.value_)
{
}

language::operator const wallet::dictionary&() const
{
    return *value_;
}

std::istream& operator>>(std::istream& input, language& argument)
{
    std::string token;
    input >> token;

    if (token == language_en)
        argument.value_ = &wallet::language::en;
    else if (token == language_es)
        argument.value_ = &wallet::language::es;
    else if (token == language_fr)
        argument.value_ = &wallet::language::fr;
    else if (token == language_it)
        argument.value_ = &wallet::language::it;
    else if (token == language_cs)
        argument.value_ = &wallet::language::cs;
    else if (token == language_pt)
        argument.value_ = &wallet::language::pt;
    else if (token == language_ja)
        argument.value_ = &wallet::language::ja;
    else if (token == language_ko)
        argument.value_ = &wallet::language::ko;
    else if (token == language_zh_Hans)
        argument.value_ = &wallet::language::zh_Hans;
    else if (token == language_zh_Hant)
        argument.value_ = &wallet::language::zh_Hant;
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(token));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const language& argument)
{
    std::string text;

    if (argument.value_ == &bc::wallet::language::en)
        text = language_en;
    else if (argument.value_ == &bc::wallet::language::es)
        text = language_es;
    else if (argument.value_ == &bc::wallet::language::fr)
        text = language_fr;
    else if (argument.value_ == &bc::wallet::language::it)
        text = language_it;
    else if (argument.value_ == &bc::wallet::language::cs)
        text = language_cs;
    else if (argument.value_ == &bc::wallet::language::pt)
        text = language_pt;
    else if (argument.value_ == &bc::wallet::language::ja)
        text = language_ja;
    else if (argument.value_ == &bc::wallet::language::ko)
        text = language_ko;
    else if (argument.value_ == &bc::wallet::language::zh_Hans)
        text = language_zh_Hans;
    else if (argument.value_ == &bc::wallet::language::zh_Hant)
        text = language_zh_Hant;
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
