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
//#include <sstream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/showtx.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>
#include <sx/utility/dispatch.hpp>

using namespace bc;

static void show_tx(const transaction_type& tx)
{
    std::cout << "hash: " << hash_transaction(tx) << std::endl;
    std::cout << "version: " << tx.version <<std::endl;
    std::cout << "locktime: " << tx.locktime << std::endl;
    for (const transaction_input_type& input: tx.inputs)
    {
        std::cout << "Input:" << std::endl;
        std::cout << "  previous output: "
            << input.previous_output.hash << ":"
            << input.previous_output.index << std::endl;
        std::cout << "  script: " << pretty(input.script) << std::endl;
        std::cout << "  sequence: " << input.sequence << std::endl;
        payment_address addr;
        if (extract(addr, input.script))
            std::cout << "  address: " << addr.encoded() << std::endl;
    }
    for (const transaction_output_type& output: tx.outputs)
    {
        std::cout << "Output:" << std::endl;
        std::cout << "  value: " << output.value << std::endl;
        std::cout << "  script: " << pretty(output.script) << std::endl;
        payment_address addr;
        if (extract(addr, output.script))
            std::cout << "  address: " << addr.encoded() << std::endl;
        if (output.script.type() == payment_type::stealth_info)
        {
            const data_chunk& data = output.script.operations()[1].data;
            BITCOIN_ASSERT(data.size() == 1 + 4 + 33);
            const data_chunk ephemkey(data.begin() + 5, data.end());
            BITCOIN_ASSERT(ephemkey.size() == 33);
            std::cout << "  stealth ephemkey: " << ephemkey << std::endl;
            std::cout << "  stealth bitfield: "
                << calculate_stealth_bitfield(data) << std::endl;
        }
    }
}

static void json_show_tx(const transaction_type& tx)
{
    std::cout << "{" << std::endl;
    std::cout << "  \"hash\": \"" << hash_transaction(tx)
        << "\"," << std::endl;
    std::cout << "  \"version\": " << tx.version << "," << std::endl;
    std::cout << "  \"locktime\": " << tx.locktime << "," << std::endl;
    std::cout << "  \"inputs\": [" << std::endl;
    bool is_first = true;
    for (const transaction_input_type& input: tx.inputs)
    {
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;
        std::cout << "   {\"previous_output\": \""
            << input.previous_output.hash << ":"
            << input.previous_output.index << "\"," << std::endl;
        std::cout << "    \"script\": \"" << pretty(input.script)
            << "\"," << std::endl;
        std::cout << "    \"sequence\": " << input.sequence
            << "," << std::endl;
        std::cout << "    \"address\": ";
        payment_address addr;
        if (extract(addr, input.script))
            std::cout << "\"" << addr.encoded() << "\"";
        else
            std::cout << "null";
        std::cout << "}";
    }
    std::cout << std::endl << "  ]," << std::endl;
    std::cout << "  \"outputs\": [" << std::endl;
    is_first = true;
    for (const transaction_output_type& output: tx.outputs)
    {
        if (is_first)
            is_first = false;
        else
            std::cout << "," << std::endl;
        std::cout << "   {\"value\": " << output.value << "," << std::endl;
        std::cout << "    \"script\": \"" << pretty(output.script)
            << "\"," << std::endl;
        std::cout << "    \"address\": ";
        payment_address addr;
        if (extract(addr, output.script))
            std::cout << "\"" << addr.encoded() << "\"";
        else
            std::cout << "null";
        std::cout << "}";
    }
    std::cout << std::endl << "  ]" << std::endl;
    std::cout << "}" << std::endl;
}

bool sx::extensions::showtx::invoke(const int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 2))
        return false;

    std::string filename(SX_STDIN_PATH_SENTINEL);
    bool json_output = get_option(argc, argv, SX_OPTION_JSON);

    for (int i = 1; i < argc; ++i)
    {
        if (is_option_any(argv[i]))
            continue;
        filename = argv[i];
    }

    transaction_type tx;
    if (!load_satoshi_item<transaction_type>(tx, filename, std::cin))
    {
        std::cerr << "sx: Deserializing transaction failed." << std::endl;
        return false;
    }

    if (json_output)
        json_show_tx(tx);
    else
        show_tx(tx);

    return true;
}

