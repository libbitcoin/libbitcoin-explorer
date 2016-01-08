/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <bitcoin/explorer/commands/qrcode.hpp>

#include <sstream>
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace bc;
using namespace bc::wallet;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result qrcode::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& address = get_payment_address_argument();
    const auto& prefix = get_prefix_option();
    const auto& image = get_image_option();
    const auto& casing = !get_ignore_casing_option();
    const auto& version = get_version_option();

#ifdef WITH_QRENCODE
    const auto qr_string = prefix + address.encoded();
    const auto qr_data = qr::encode(to_chunk(qr_string),
        version, qr::level, qr::mode, casing);

    // The image option specifies we're writing output in png format.
    if (image)
    {
#ifdef WITH_PNG
        const auto& size = get_size_option();
        const auto& density = get_density_option();
        const auto& margin = get_margin_option();

        auto result = png::write_png(qr_data, size, density, margin,
            png::inches_per_meter, png::get_default_foreground(),
            png::get_default_background(), output);

        return (result ? console_result::okay : console_result::failure);
#else
        error << BX_QRCODE_REQUIRES_PNG << std::endl;
        return console_result::failure;
#endif // WITH_PNG
    }

    // In this case, the qr data is written to the output stream in
    // encoded 'qrencode' format.
    bc::ostream_writer sink(output);
    sink.write_data(qr_data);
    output.flush();

    return console_result::okay;
#else
    error << BX_QRCODE_REQUIRES_QRENCODE << std::endl;
    return console_result::failure;
#endif // WITH_QRENCODE
}
