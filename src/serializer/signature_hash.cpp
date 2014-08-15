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
#include "precompile.hpp"
#include <sx/serializer/signature_hash.hpp>

#include <exception>
#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

using namespace bc;
using namespace po;

namespace sx {
namespace serializer {

// DRY
static const char* signature_hash_all = "all";
static const char* signature_hash_none = "none";
static const char* signature_hash_single = "single";
static const char* signature_hash_anyone_can_pay = "anyone_can_pay";

signature_hash::signature_hash()
    : signature_hash(sighash::single)
{
}

signature_hash::signature_hash(const std::string& token)
{
    std::stringstream(token) >> *this;
}

signature_hash::signature_hash(const sighash& value)
    : value_(value)
{
}

signature_hash::signature_hash(const signature_hash& other)
    : value_(other.value_)
{
}

signature_hash::operator const sighash() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, signature_hash& argument)
{
    std::string text;
    input >> text;

    if (text == signature_hash_all)
        argument.value_ = sighash::all;
    else if (text == signature_hash_none)
        argument.value_ = sighash::none;
    else if (text == signature_hash_single)
        argument.value_ = sighash::single;
    else if (text == signature_hash_anyone_can_pay)
        argument.value_ = sighash::anyone_can_pay;
    else
        throw invalid_option_value(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const signature_hash& argument)
{
    std::string value;

    switch (argument.value_)
    {
        case sighash::all:
            value = signature_hash_all;
            break;
        case sighash::none:
            value = signature_hash_none;
            break;
        case sighash::single:
            value = signature_hash_single;
            break;
        case sighash::anyone_can_pay:
            value = signature_hash_anyone_can_pay;
            break;
        default:
            throw std::exception("Unexpected signature hash type value.");
    }

    return output;
}

} // sx
} // serializer