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
#include <bitcoin/explorer/primitives/transaction.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/base16.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace po;

namespace libbitcoin {
namespace explorer {
namespace primitives {

transaction::transaction()
    : value_()
{
}

transaction::transaction(const std::string& hexcode)
{
    std::stringstream(hexcode) >> *this;
}

transaction::transaction(const tx_type& value)
    : value_(value)
{
}

transaction::transaction(const transaction& other)
    : transaction(other.value_)
{
}

tx_type& transaction::data()
{
    return value_;
}

transaction::operator const tx_type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, transaction& argument)
{
    std::string hexcode;
    input >> hexcode;

    // tx base16 is a private encoding in bx, used to pass between commands.
    if (!deserialize_satoshi_item(argument.value_, base16(hexcode)))
        BOOST_THROW_EXCEPTION(invalid_option_value(hexcode));

    return input;
}

std::ostream& operator<<(std::ostream& output, const transaction& argument)
{
    // tx base16 is a private encoding in bx, used to pass between commands.
    const auto bytes = serialize_satoshi_item(argument.value_);
    output << base16(bytes);
    return output;
}

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
