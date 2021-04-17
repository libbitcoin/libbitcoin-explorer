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
#ifndef BX_WRAPPER_HPP
#define BX_WRAPPER_HPP

#include <cstdint>
#include <iostream>
#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

// TODO: remove wrap/unwrap commands and remove this.

class BCX_API wrapper
{
public:
    typedef system::wallet::wrapped_data type;

    wrapper();
    wrapper(const wrapper& other);
    wrapper(const std::string& token);
    wrapper(const type& value);

    // TODO remove.
    wrapper::wrapper(const system::data_chunk& wrapped);

    // TODO remove.
    wrapper::wrapper(const system::wallet::payment_address& address);

    // TODO remove.
    wrapper(uint8_t version, const system::data_chunk& payload);

    // TODO remove.
    system::data_chunk to_data() const;

    operator const type&() const;

    friend std::istream& operator>>(std::istream& input, wrapper& argument);
    friend std::ostream& operator<<(std::ostream& output,
        const wrapper& argument);

private:
    type value_;
};

} // namespace explorer
} // namespace config
} // namespace libbitcoin

#endif
