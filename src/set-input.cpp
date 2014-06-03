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
#include <sx/command/set-input.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result set_input::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 4, 4))
        return console_result::failure;

    transaction_type tx;
    const auto filename(get_filename(argc, argv));
    if (!load_satoshi_item<transaction_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return console_result::failure;
    }

    size_t input_index;
    if (!parse<size_t>(argv[2], input_index))
    {
        std::cerr << "set-input: Bad N provided." << std::endl;
        return console_result::failure;
    }

    if (input_index >= tx.inputs.size())
    {
        std::cerr << "set-input: N out of range." << std::endl;
        return console_result::failure;
    }

    const auto raw_script = decode_hex(argv[3]);
    const auto new_input_script = raw_data_script(raw_script);

    // Set input.
    tx.inputs[input_index].script = new_input_script;

    // Now re-serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    std::cout << raw_tx << std::endl;
    return console_result::okay;
}

