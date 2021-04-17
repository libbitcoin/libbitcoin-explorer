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
#include <bitcoin/explorer/config/endorsement.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

endorsement::endorsement()
  : value_()
{
}

endorsement::endorsement(const endorsement& other)
  : endorsement(other.value_)
{
}

endorsement::endorsement(const std::string& token)
{
    std::stringstream(token) >> *this;
}

endorsement::endorsement(const type& value)
  : value_(value)
{
}

endorsement::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, endorsement& argument)
{
    std::string text;
    input >> text;

    endorsement::type out;
    if (!system::decode_base16(out, text) ||
        (out.size() > system::max_endorsement_size))
        throw_istream_failure(text);

    argument.value_ = out;
    return input;
}

std::ostream& operator<<(std::ostream& output, const endorsement& argument)
{
    output << system::encode_base16(argument.value_);
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
