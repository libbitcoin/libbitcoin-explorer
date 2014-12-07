/**
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

#include <bitcoin/explorer/commands/input-validate.hpp>

#include <iostream>
#include <cstdint>
#include <bitcoin/bitcoin.hpp>

using namespace bc;
using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result message_validate::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& address = get_bitcoin_address_argument();
    const data_chunk& signature_bytes = get_signature_argument();
    const auto& message = get_message_argument();

    // This is a hack that prevents us from having to create a primitive for
    // message_signatures as a data type and instead just treat it as base16.

    if (signature_bytes.size() != message_signature_size)
    {
        output << BX_MESSAGE_VALIDATE_INDEX_INVALID_SIGNATURE_FORMAT << std::endl;
        return console_result::failure;
    }

    message_signature signature;
    std::copy(signature_bytes.begin(), signature_bytes.end(),
        signature.begin());

    if (!verify_message(message, address, signature))
    {
        output << BX_MESSAGE_VALIDATE_INDEX_INVALID_SIGNATURE << std::endl;
        return console_result::invalid;
    }

    output << BX_MESSAGE_VALIDATE_INDEX_VALID_SIGNATURE << std::endl;
    return console_result::okay;
}

