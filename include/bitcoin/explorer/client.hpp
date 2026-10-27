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
#ifndef BX_CLIENT_HPP
#define BX_CLIENT_HPP

#include <string>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

/// Synchronous client for the libbitcoin server native interface.
class BCX_API client
{
public:
    /// Construct a client for the given service url.
    client(const system::config::url& url, uint8_t retries,
        uint16_t timeout_seconds) NOEXCEPT;

    /// Get the json response for a native interface path, such as
    /// "block/height/42". The version prefix and format are supplied here.
    /// Returns false and sets error on transport, status or decode failure.
    bool get(system::json::value& out, std::string& error,
        const std::string& path) NOEXCEPT;

private:
    const system::config::url url_;
    const uint8_t retries_;
    const uint16_t timeout_seconds_;
};

} // namespace explorer
} // namespace libbitcoin

#endif
