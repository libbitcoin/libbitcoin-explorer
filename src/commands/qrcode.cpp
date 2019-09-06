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

#include <sstream>
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
#ifdef WITH_QRENCODE
    // Bound parameters.
    const auto& image = get_png_option();
    const auto& insensitive = get_insensitive_option();
    const auto& scheme = get_scheme_option();
    const auto& version = get_version_option();
    const auto& address = get_payment_address_argument();

    const auto delimiter = scheme.empty() ? "" : ":";
    const auto qr_string = scheme + delimiter + address.encoded();
    const auto qr_data = qr::encode(to_chunk(qr_string), version, qr::level,
        qr::mode, !insensitive);

    // The image option specifies we're writing output in png format.
    if (image)
    {
#ifdef WITH_PNG
        const auto& density = get_density_option();
        const auto& margin = get_margin_size_option();
        const auto& module = get_module_size_option();

        const auto result = png::write_png(qr_data, module, density, margin,
            png::inches_per_meter, png::get_default_foreground(),
            png::get_default_background(), output);

        return (result ? console_result::okay : console_result::failure);
#else
        error << BX_QRCODE_REQUIRES_PNG << std::endl;
        return console_result::failure;
#endif // WITH_PNG
    }

    // The qr data is written to the output stream in 'qrencode' format.
    ostream_writer sink(output);
    sink.write_bytes(qr_data);
    output.flush();

    return console_result::okay;
#else
    error << BX_QRCODE_REQUIRES_QRENCODE << std::endl;
    return console_result::failure;
#endif // WITH_QRENCODE
}

} //namespace commands
} //namespace explorer
} //namespace libbitcoin
