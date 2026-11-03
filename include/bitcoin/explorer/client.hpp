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

class command;

/// Synchronous client for the libbitcoin server native interface.
class BCX_API client
{
public:
    /// Construct a client for the given service url.
    client(const system::config::url& url, uint8_t retries,
        uint16_t timeout_seconds) NOEXCEPT;

    /// Construct a client for the command's server, from the url argument
    /// when it specifies a port and otherwise from the url setting.
    client(const command& command,
        const system::config::url& argument) NOEXCEPT;

    /// Get the json response for a native interface path, such as
    /// "block/height/42". The version prefix and format are supplied here,
    /// and query is appended to the format parameter, such as "witness=false".
    /// Returns false and sets error on transport, status or decode failure.
    bool get(system::json::value& out, std::string& error,
        const std::string& path, const std::string& query="") NOEXCEPT;

    /// Get as above, writing the failure message to the error stream.
    bool fetch(system::json::value& out, std::ostream& error,
        const std::string& path, const std::string& query="") NOEXCEPT;

private:
    const system::config::url url_;
    const uint8_t retries_;
    const uint16_t timeout_seconds_;
};

/// The native interface path of a block, by hash unless the hash is null
/// and otherwise by height, such as "block/height/42".
BCX_API std::string block_path(const system::hash_digest& hash,
    uint32_t height) NOEXCEPT;

} // namespace explorer
} // namespace libbitcoin

#endif
