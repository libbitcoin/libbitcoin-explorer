/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
#ifndef BX_BYTES_HPP
#define BX_BYTES_HPP

#include <iostream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

// This is the default bytes reader.

class BCX_API bytes
{
public:
    typedef system::data_chunk type;

    bytes();
    bytes(const bytes& other);
    bytes(const std::string& token);
    bytes(const type& value);

    operator const type&() const;

    friend std::istream& operator>>(std::istream& input, bytes& argument);
    friend std::ostream& operator<<(std::ostream& output,
        const bytes& argument);

private:
    type value_;
};

} // namespace explorer
} // namespace config
} // namespace libbitcoin

#endif
