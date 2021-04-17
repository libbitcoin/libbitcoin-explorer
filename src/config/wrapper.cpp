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
#include <bitcoin/explorer/config/wrapper.hpp>

#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/utility.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

// This recalculates the checksum, ignoring data.checksum.
static system::data_chunk wrap(const system::wallet::wrapped_data& data)
{
    auto wrapper = system::build_chunk(
    {
        system::data_chunk(data.version),
        data.payload
    });
    system::append_checksum(wrapper);
    return wrapper;
}

// This verifies the checksum.
static bool unwrap(system::wallet::wrapped_data& data,
    const system::data_chunk& wrapped)
{
    if (!system::verify_checksum(wrapped))
        return false;

    const auto payload = std::next(wrapped.begin());
    const auto checksum = std::prev(wrapped.end(), system::checksum_size);

    data.version = wrapped.front();
    data.payload.assign(payload, checksum);
    data.checksum = system::from_little_endian_unsafe<uint32_t>(checksum);
    return true;
}

wrapper::wrapper()
  : value_()
{
}

wrapper::wrapper(const wrapper& other)
  : value_(other.value_)
{
}

wrapper::wrapper(const std::string& token)
{
    std::stringstream(token) >> *this;
}

wrapper::wrapper(const type& value)
  : value_(value)
{
}

// TODO remove.
wrapper::wrapper(const system::data_chunk& wrapped)
  : wrapper(system::encode_base16(wrapped))
{
}

// TODO remove.
wrapper::wrapper(const system::wallet::payment_address& address)
  : wrapper(system::encode_base16(address.to_payment()))
{
}

// TODO remove.
wrapper::wrapper(uint8_t version, const system::data_chunk& payload)
  : value_(system::wallet::wrapped_data{ version, payload, 0 })
{
}

// TODO remove.
system::data_chunk wrapper::to_data() const
{
    return wrap(value_);
}

wrapper::operator const type&() const
{
    return value_;
}

std::istream& operator>>(std::istream& input, wrapper& argument)
{
    std::string text;
    input >> text;

    // The checksum is validated here.
    if (!unwrap(argument.value_, system::config::base16(text)))
        throw_istream_failure(text);

    return input;
}

std::ostream& operator<<(std::ostream& output, const wrapper& argument)
{
    const auto bytes = wrap(argument.value_);
    output << system::config::base16(bytes);
    return output;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
