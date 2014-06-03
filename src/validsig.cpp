/**
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
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/validsig.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

static bool valid_signature(const transaction_type& tx,
    const uint32_t input_index, elliptic_curve_key& key, 
    const script_type& script_code, data_chunk signature)
{
    const auto hash_type = signature.back();
    signature.pop_back();
    auto tx_hash = script_type::generate_signature_hash(
        tx, input_index, script_code, hash_type);
    return key.verify(tx_hash, signature);
}

bool sx::extensions::validsig::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 5, 5))
        return false;

    transaction_type tx;
    const std::string filename(get_filename(argc, argv));
    if (!load_satoshi_item<transaction_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return false;
    }

    uint32_t input_index;
    if (!parse<uint32_t>(argv[2], input_index))
    {
        std::cerr << "validsig: Bad N provided." << std::endl;
        return false;
    }

    if (input_index >= tx.inputs.size())
    {
        std::cerr << "validsig: N out of range." << std::endl;
        return false;
    }

    elliptic_curve_key key;
    if (!read_public_or_private_key(key, std::cin))
    {
        std::cerr << "Invalid public or private key." << std::endl;
        return false;
    }

    const auto script = parse_script(decode_hex(argv[3]));
    const auto signature = decode_hex(argv[4]);

    // These output strings should probably be basic boolean as they will 
    // become dependended upon in script code that uses sx.
    if (valid_signature(tx, input_index, key, script, signature))
        std::cout << "Status: Failed" << std::endl;
    else
        std::cout << "Status: OK" << std::endl;

    return true;
}

