/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include <explorer/primitives/hashtype.hpp>

#include <exception>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// DRY
static const char* hashtype_all = "all";
static const char* hashtype_none = "none";
static const char* hashtype_single = "single";
static const char* hashtype_anyone_can_pay = "anyone_can_pay";

hashtype::hashtype()
    : hashtype(sighash::single)
{
}

hashtype::hashtype(const std::string& token)
{
    std::stringstream(token) >> *this;
}

hashtype::hashtype(const sighash& value)
    : value_(value)
{
}

hashtype::hashtype(const hashtype& other)
    : value_(other.value_)
{
}

hashtype::operator sighash() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, hashtype& argument)
{
    std::string text;
    input >> text;

    if (text == hashtype_all)
        argument.value_ = sighash::all;
    else if (text == hashtype_none)
        argument.value_ = sighash::none;
    else if (text == hashtype_single)
        argument.value_ = sighash::single;
    else if (text == hashtype_anyone_can_pay)
        argument.value_ = sighash::anyone_can_pay;
    else
        throw invalid_option_value(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const hashtype& argument)
{
    std::string value;

    switch (argument.value_)
    {
        case sighash::all:
            value = hashtype_all;
            break;
        case sighash::none:
            value = hashtype_none;
            break;
        case sighash::single:
            value = hashtype_single;
            break;
        case sighash::anyone_can_pay:
            value = hashtype_anyone_can_pay;
            break;
        default:
            throw std::exception(/*"Unexpected signature hash type value."*/);
    }

    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
