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
#include <bitcoin/explorer/commands/qrcode.hpp>

#include <iostream>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace commands {

using namespace bc::system;
using namespace bc::system::wallet;

console_result qrcode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto margin_size = get_margin_option();
    const auto scale_factor = get_pixels_option();
    const auto uri_scheme = get_scheme_option();
    const auto qrcode_version = get_version_option();
    const auto& address = get_payment_address_argument();

    const auto delimiter = uri_scheme.empty() ? "" : ":";
    const auto value = uri_scheme + delimiter + address.encoded();

    if (qrcode_version > qr_code::maximum_version)
    {
        error << BX_QRCODE_MAXIMUM_VERSION << std::endl;
        return console_result::failure;
    }

    if (scale_factor == 0u)
    {
        error << BX_QRCODE_MINIMUM_SIZE << std::endl;
        return console_result::failure;
    }

    // Because the parser cannot support uint8_t types.
    const auto version = static_cast<uint8_t>(qrcode_version);

    if (!qr_code::encode(output, value, version, scale_factor, margin_size))
    {
        error << BX_QRCODE_MAXIMUM_SIZE << std::endl;
        return console_result::failure;
    }

    output.flush();
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
