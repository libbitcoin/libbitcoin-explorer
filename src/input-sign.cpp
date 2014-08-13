/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include "precompile.hpp"
#include <sx/command/input-sign.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

static bool sign(tx_type& tx, uint32_t input_index,
    const elliptic_curve_key& key, const script_type& script_code)
{
    tx_input_type& input = tx.inputs[input_index];
    const data_chunk public_key = key.public_key();
    if (public_key.empty())
    {
        std::cerr << "sign-input: Internal error getting public key."
            << std::endl;
        return false;
    }

    const auto tx_hash = script_type::generate_signature_hash(tx, input_index,
        script_code, 1);
    if (tx_hash == null_hash)
    {
        std::cerr << "sign-input: Error generating signature hash."
            << std::endl;
        return false;
    }

    auto signature = key.sign(tx_hash);

    // Magic Number?
    signature.push_back(0x01);
    std::cout << signature << std::endl;
    return true;
}

console_result input_sign::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 4, 4))
        return console_result::failure;

    tx_type tx;
    const auto filename(get_filename(argc, argv));
    if (!load_satoshi_item<tx_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return console_result::failure;
    }

    uint32_t input_index;
    if (!parse(input_index, argv[2]))
    {
        std::cerr << "sign-input: Bad N provided." << std::endl;
        return console_result::failure;
    }

    const auto script_code = parse_script(decode_hex(argv[3]));
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "sign-input: N out of range." << std::endl;
        return console_result::failure;
    }

    elliptic_curve_key signing_key;
    if (!read_private_key(signing_key, std::cin))
    {
        std::cerr << "Invalid private key." << std::endl;
        return console_result::failure;
    }

    auto okay = sign(tx, input_index, signing_key, script_code);
    return if_else(okay, console_result::okay, console_result::failure);
}

