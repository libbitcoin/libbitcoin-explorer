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

#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

#define BX_JSON_INVALID "The input is not valid JSON."
#define BX_JSON_MISSING "The property is not present."
#define BX_JSON_NOT_LIST "The property is not a list."
#define BX_JSON_OUT_OF_RANGE "The index is out of range."

namespace libbitcoin {
namespace explorer {

BCX_API system::json::value to_json(
    const system::wallet::bitcoin_uri& uri) NOEXCEPT;

/// The version, payload and checksum of bitcoin checked data.
BCX_API system::json::value checked_to_json(
    const system::data_chunk& checked) NOEXCEPT;

/// Write the named property of a JSON object, a string without quotes.
BCX_API console_result write_property(std::ostream& output,
    std::ostream& error, const std::string& json, const std::string& name);

/// Write the indexed element of the named list property of a JSON object.
BCX_API console_result write_element(std::ostream& output,
    std::ostream& error, const std::string& json, const std::string& name,
    uint32_t index);

} // namespace explorer
} // namespace libbitcoin

#endif
