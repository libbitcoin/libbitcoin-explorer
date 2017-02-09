/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/explorer/commands/base58check-encode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {
using namespace bc::config;
using namespace bc::explorer::config;

console_result base58check_encode::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto version = get_version_option();
    const auto& payload = get_base16_argument();

    const wrapper wrapped(version, payload);
    const auto encoded_wrapper = wrapped.to_data();
    const base58 base58check(encoded_wrapper);

    output << base58check << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
