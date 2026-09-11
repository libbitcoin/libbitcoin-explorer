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
#ifndef BX_EC_PRIVATE_HPP
#define BX_EC_PRIVATE_HPP

#include <iostream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

class BCX_API ec_private
{
public:
    typedef system::ec_secret type;

    ec_private();
    ec_private(const ec_private& other);
    ec_private(const std::string& token);
    ec_private(const type& value);

    operator const type&() const;

    friend std::istream& operator>>(std::istream& input, ec_private& argument);
    friend std::ostream& operator<<(std::ostream& output,
        const ec_private& argument);

private:
    type value_;
};

} // namespace explorer
} // namespace config
} // namespace libbitcoin

#endif
