/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/primitives/script.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

script::script()
    : value_()
{
}

script::script(const std::string& mnemonic)
{
    std::stringstream(mnemonic) >> *this;
}

script::script(const script_type& value)
    : value_(value)
{
}

script::script(const data_chunk& value)
    : value_(parse_script(value))
{
}

script::script(const std::vector<std::string>& tokens)
{
    const auto mnemonic = join(tokens);
    std::stringstream(mnemonic) >> *this;
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

script::operator const data_chunk() const
{
    return base16(save_script(value_));
}

std::istream& operator>>(std::istream& input, script& argument)
{
    std::istreambuf_iterator<char> eos;
    std::string mnemonic(std::istreambuf_iterator<char>(input), eos);
    trim(mnemonic);

    argument.value_ = unpretty(mnemonic);

    // Test for invalid result sentinel.
    if (argument.value_.operations().size() == 0 && mnemonic.length() > 0)
        throw invalid_option_value(mnemonic);

    return input;
}

std::ostream& operator<<(std::ostream& output, const script& argument)
{
    output << pretty(argument.value_);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
