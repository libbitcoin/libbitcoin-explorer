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
#include <sx/utility/console.hpp>

using namespace bc;

bool invoke(const int argc, const char* argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: set-input FILENAME N SIGNATURE_AND_PUBKEY_SCRIPT" << std::endl;
        return -1;
    }
    const std::string filename = argv[1];
    transaction_type tx;
    if (!load_tx(tx, filename))
        return -1;
    const std::string index_str = argv[2];
    size_t input_index;
    try
    {
        input_index = boost::lexical_cast<size_t>(index_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "set-input: Bad N provided." << std::endl;
        return -1;
    }
    if (input_index >= tx.inputs.size())
    {
        std::cerr << "set-input: N out of range." << std::endl;
        return -1;
    }

    std::string hex_script = argv[3]; 
    script_type new_input_script = raw_data_script(decode_hex(hex_script));
    // Set input.
    tx.inputs[input_index].script = new_input_script;
    // Now re-serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());
    std::cout << raw_tx << std::endl;
    return 0;
}

