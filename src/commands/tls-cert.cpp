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

#include <bitcoin/explorer/commands/tls-cert.hpp>

#include <chrono>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;

constexpr uint64_t seconds_per_day = 86400;
constexpr uint64_t year_10000 = 253402300800;

static uint64_t now() NOEXCEPT
{
    using namespace std::chrono;
    const auto elapsed = system_clock::now().time_since_epoch();
    return sign_cast<uint64_t>(duration_cast<seconds>(elapsed).count());
}

static data_chunk to_bytes(const ip::address& address) NOEXCEPT
{
    return address.is_v4() ? to_chunk(address.to_v4().to_bytes()) :
        to_chunk(address.to_v6().to_bytes());
}

console_result tls_cert::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& key = get_private_key_argument();
    const auto& name = get_name_option();
    const auto& hosts = get_hosts_option();
    const auto& ips = get_ips_option();
    const auto not_before = get_not_before_option();
    const auto days = get_days_option();

    x509::secret secret{};
    secp256r1::point_t point{};
    if (!x509::decode_private_key(secret, key) ||
        !secp256r1::public_key(point, secret))
    {
        error << BX_TLS_CERT_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    if (name.empty() && hosts.empty() && ips.empty())
    {
        error << BX_TLS_CERT_UNNAMED << std::endl;
        return console_result::failure;
    }

    x509::subject subject{};
    subject.common_name = name;
    subject.dns_names = hosts;
    for (const auto& text: ips)
    {
        ip::address address{};
        if (!ip::address::from_string(address, text))
        {
            error << BX_TLS_CERT_INVALID_IP << std::endl;
            return console_result::failure;
        }

        subject.ip_addresses.push_back(to_bytes(address));
    }

    const auto hash = sha256_hash(point);
    std::copy_n(hash.begin(), subject.serial.size(), subject.serial.begin());
    subject.not_before = is_zero(not_before) ? now() : not_before;
    subject.not_after = ceilinged_add(subject.not_before,
        days * seconds_per_day);
    if (subject.not_after >= year_10000)
    {
        error << BX_TLS_CERT_INVALID_VALIDITY << std::endl;
        return console_result::failure;
    }

    data_chunk certificate{};
    if (!x509::build_self_signed(certificate, secret, subject))
    {
        error << BX_TLS_CERT_INVALID_KEY << std::endl;
        return console_result::failure;
    }

    output << x509::encode_certificate(certificate);
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
