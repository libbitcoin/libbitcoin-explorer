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
#ifndef BX_HD_KEY_HPP
#define BX_HD_KEY_HPP

#include <iostream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

// Base58 reader of hd_key_size.

class BCX_API hd_key
{
public:
    typedef system::wallet::hd_key type;

    hd_key();
    hd_key(const hd_key& other);
    hd_key(const std::string& token);
    hd_key(const type& value);

    // TODO: remove.
    uint32_t hd_key::version() const;

    operator const type&() const;

    friend std::istream& operator>>(std::istream& input, hd_key& argument);
    friend std::ostream& operator<<(std::ostream& output,
        const hd_key& argument);

private:
    type value_;
};

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#endif
