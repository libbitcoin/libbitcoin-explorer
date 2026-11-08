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

#include <bitcoin/explorer/commands/version.hpp>

#include <format>
#include <bitcoin/network.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/version.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

template <typename Version>
static std::string thumb(const Version& version) NOEXCEPT
{
    return std::format("{} {}{}", version.semantic,
        version.commit_hash.substr(0, 8), version.dirty ? "-dirty" : "");
}

console_result version::invoke(std::ostream& output, std::ostream&)
{
    output << BX_VERSION_HEADER << std::endl;
    output << "secp256k1............ " << system::secp256k1_library() << std::endl;
    output << "tls.................. " << network::tls_library() << std::endl;
    output << "libbitcoin-system.... " << thumb(system::build_version()) << std::endl;
    output << "libbitcoin-network... " << thumb(network::build_version()) << std::endl;
    output << "libbitcoin-explorer.. " << thumb(explorer::build_version()) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
