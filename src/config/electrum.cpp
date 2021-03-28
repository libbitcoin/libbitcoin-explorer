/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/config/electrum.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc;
using namespace po;

static auto electrum_standard = "standard";
static auto electrum_witness = "witness";
static auto electrum_two_factor_authentication = "dual";

electrum::electrum()
  : value_(wallet::electrum::seed::standard)
{
}

electrum::electrum(const std::string& token)
{
    std::stringstream(token) >> *this;
}

electrum::electrum(wallet::electrum::seed& electrum)
  : value_(electrum)
{
}

electrum::electrum(const electrum& other)
  : value_(other.value_)
{
}

electrum::operator wallet::electrum::seed() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, electrum& argument)
{
    std::string text;
    input >> text;

    if (text == electrum_standard)
    {
        argument.value_ = wallet::electrum::seed::standard;
    }
    else if (text == electrum_witness)
    {
        argument.value_ = wallet::electrum::seed::witness;
    }
    else if (text == electrum_two_factor_authentication)
    {
        argument.value_ = wallet::electrum::seed::two_factor_authentication;
    }
    else
    {
        BOOST_THROW_EXCEPTION(invalid_option_value(text));
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const electrum& argument)
{
    std::string text;

    if (argument.value_ == wallet::electrum::seed::standard)
    {
        text = electrum_standard;
    }
    else if (argument.value_ == wallet::electrum::seed::witness)
    {
        text = electrum_witness;
    }
    else if (argument.value_ == wallet::electrum::seed::two_factor_authentication)
    {
        text = electrum_two_factor_authentication;
    }
    else
    {
        BITCOIN_ASSERT_MSG(false, "Unexpected electrum value.");
    }

    output << text;
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
