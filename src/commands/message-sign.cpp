/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/commands/input-sign.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/primitives/base64.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;
using namespace bc::explorer::primitives;

console_result message_sign::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    const auto& wif = get_wif_argument();
    const auto& message = get_message_argument();

    // This is a hack that prevents us from having to create a primitive for
    // message_signatures as a data type and instead just treat it as base16.

    auto signature = sign_message(message, wif);

    data_chunk signature_bytes;
    std::copy(signature_bytes.begin(), signature_bytes.end(),
        signature.begin());

    output << base64(signature_bytes) << std::endl;
    return console_result::okay;
}
