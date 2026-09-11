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
#ifndef BX_JSON_HPP
#define BX_JSON_HPP

#include <boost/json.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

/// Serializations for types not annotated by libbitcoin-system.

BCX_API boost::json::value to_json(const settings_list& settings) NOEXCEPT;

BCX_API boost::json::value to_json(
    const system::wallet::stealth_address& address) NOEXCEPT;

BCX_API boost::json::value to_json(
    const system::wallet::bitcoin_uri& uri) NOEXCEPT;

} // namespace explorer
} // namespace libbitcoin

#endif
