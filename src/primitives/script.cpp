/**
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
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
#include <explorer/primitives/script.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <explorer/define.hpp>
#include <explorer/primitives/base16.hpp>
#include <explorer/utility/utility.hpp>

using namespace bc;
using namespace po;

namespace explorer {
namespace primitives {

script::script()
    : value_()
{
}

script::script(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

script::script(const script_type& value)
    : value_(value)
{
}

script::script(const std::vector<std::string>& mnemonics)
{
    std::string script;
    join(mnemonics, script);

    value_ = unpretty(script);
    if (value_.operations().empty())
        throw invalid_option_value(script);
}

script::script(const script& other)
    : script(other.value_)
{
}

const std::string script::mnemonic() const
{
    return pretty(value_);
}

script::operator const script_type&() const
{
    return value_; 
}

std::istream& operator>>(std::istream& input, script& argument)
{
    std::string hexcode;
    input >> hexcode;

    try
    {
        argument.value_ = parse_script(base16(hexcode));
    }
    catch (end_of_stream)
    {
        throw invalid_option_value(hexcode);
    }

    return input;
}

std::ostream& operator<<(std::ostream& output, const script& argument)
{
    output << base16(save_script(argument.value_));
    return output;
}

} // explorer
} // primitives
