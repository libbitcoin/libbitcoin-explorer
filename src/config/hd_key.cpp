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
#include <bitcoin/explorer/config/hd_key.hpp>

#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace bc::system;

hd_key::hd_key()
  : value_()
{
}

hd_key::hd_key(const hd_key& other)
  : value_(other.value_)
{
}

hd_key::hd_key(const std::string& token)
{
    std::stringstream(token) >> *this;
}


hd_key::hd_key(const type& value)
  : value_(value)
{
}

////uint32_t hd_key::version() const
////{
////    return from_big_endian_unsafe<uint32_t>(value_.begin());
////}

hd_key::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, hd_key& argument)
{
    std::string text;
    input >> text;

    data_chunk value;
    if (!decode_base58(value, text) || value.size() != wallet::hd_key_size)
        throw_istream_failure(text);

    std::copy(value.begin(), value.end(), argument.value_.begin());
    return input;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
