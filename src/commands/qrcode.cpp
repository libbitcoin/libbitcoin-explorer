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
    const auto scale_factor = get_module_option();
    const auto url_scheme = get_scheme_option();
    const auto qrcode_version = get_version_option();
    const auto& address = get_payment_address_argument();

    const auto delimiter = url_scheme.empty() ? "" : ":";
    const auto value = url_scheme + delimiter + address.encoded();

    if (qrcode_version > qr_code::maximum_version)
    {
        error << BX_QRCODE_MAXIMUM_VERSION << std::endl;
        return console_result::failure;
    }

    // For raw bit stream set scale=1 and margin=0.
    // The image is at file offset bc::tiff::image_offset to EOF.
    // If image-pixel-width^2 % 8 != 0 then last byte contains padding.
    if (!qr_code::encode(output, value, qrcode_version, scale_factor,
        margin_size))
    {
        error << BX_QRCODE_GENERATION_ERROR << std::endl;
        return console_result::failure;
    }

    output.flush();
    return console_result::okay;
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
