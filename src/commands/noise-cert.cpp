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
#include <bitcoin/explorer/commands/noise-cert.hpp>

#include <chrono>
#include <bitcoin/network.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::network::noise;
using namespace bc::system;

constexpr uint64_t seconds_per_day = 86400;

static uint64_t now() NOEXCEPT
{
    using namespace std::chrono;
    const auto elapsed = system_clock::now().time_since_epoch();
    return sign_cast<uint64_t>(duration_cast<seconds>(elapsed).count());
}

console_result noise_cert::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const ec_secret& authority = get_authority_private_key_argument();
    const auto& server = get_server_public_key_argument();
    const auto valid_from = get_valid_from_option();
    const auto days = get_days_option();
    const data_chunk& auxiliary = get_auxiliary_option();

    hash_digest entropy{};
    if (!auxiliary.empty())
    {
        if (auxiliary.size() != entropy.size())
        {
            error << BX_NOISE_CERT_INVALID_AUXILIARY << std::endl;
            return console_result::failure;
        }

        std::copy(auxiliary.begin(), auxiliary.end(), entropy.begin());
    }

    const uint64_t from = is_zero(valid_from) ? now() : valid_from;
    const auto until = from + days * seconds_per_day;
    if (until > max_uint32)
    {
        error << BX_NOISE_CERT_INVALID_VALIDITY << std::endl;
        return console_result::failure;
    }

    certificate::data out{};
    if (!certificate::sign(out, authority,
        certificate::to_xonly(server.point()),
        possible_narrow_cast<uint32_t>(from),
        possible_narrow_cast<uint32_t>(until), entropy))
    {
        error << BX_NOISE_CERT_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << encode_base16(out) << std::endl;
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
