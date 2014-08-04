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
#include <sx/command/tx-encode.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/utility/dispatch.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace libwallet;
using namespace sx;
using namespace sx::extensions;

// Currently unused.
//static int display_help()
//{
//    puts("Usage: mktx FILENAME [ARGS]...");
//    puts("");
//    puts("Options:");
//    puts("");
//    puts(" -i, --input\tPrevious output in the form TXHASH:INDEX");
//    puts(" -o, --output\tSpecify a destination ADDRESS:AMOUNT");
//    puts("\t\tor HEXSCRIPT:AMOUNT");
//    puts("\t\tAMOUNT uses internal bitcoin values");
//    puts("\t\t  0.1 BTC = 0.1 * 10^8 = 10000000");
//    puts("");
//    puts("Please email suggestions and questions to <genjix@riseup.net>.");
//    return -1;
//}

static bool two_args_remain(size_t current_arg, int argc)
{
    return argc - current_arg >= 2;
}

static bool load_outpoint(output_point& prevout, const std::string& parameter)
{
    std::vector<std::string> words;
    split(parameter, words, ":");
    if (words.size() != 2)
    {
        std::cerr << "mktx: Format for previous output is TXHASH:INDEX."
            << std::endl;
        return false;
    }

    // Magic Number?
    const std::string& hex_string = words.front();
    if (hex_string.size() != 64)
    {
        std::cerr << "mktx: Incorrect TXHASH." << std::endl;
        return false;
    }

    prevout.hash = decode_hash(hex_string);
    const std::string& index_string = words[1];
    try
    {
        prevout.index = boost::lexical_cast<uint32_t>(index_string);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "mktx: Bad INDEX provided." << std::endl;
        return false;
    }

    return true;
}

static bool add_input(transaction_type& tx, const std::string& parameter)
{
    transaction_input_type input;
    output_point& prevout = input.previous_output;
    if (!load_outpoint(prevout, parameter))
        return false;

    // Magic Number?
    input.sequence = 4294967295;
    tx.inputs.push_back(input);
    std::cerr << "Added input " << prevout.hash << ":" << prevout.index 
        << std::endl;
    return true;
}

static bool change_locktime(transaction_type& tx, const std::string& parameter)
{
    tx.locktime = atoi(parameter.c_str());
    return true;
}

static script_type build_pubkey_hash_script(const short_hash& pubkey_hash)
{
    script_type result;
    result.push_operation({opcode::dup, data_chunk()});
    result.push_operation({opcode::hash160, data_chunk()});
    result.push_operation({opcode::special,
        data_chunk(pubkey_hash.begin(), pubkey_hash.end())});
    result.push_operation({opcode::equalverify, data_chunk()});
    result.push_operation({opcode::checksig, data_chunk()});
    return result;
}

static script_type build_script_hash_script(const short_hash& script_hash)
{
    script_type result;
    result.push_operation({opcode::hash160, data_chunk()});
    result.push_operation({opcode::special,
        data_chunk(script_hash.begin(), script_hash.end())});
    result.push_operation({opcode::equal, data_chunk()});
    return result;
}

static bool build_output_script(
    script_type& out_script, const payment_address& payaddr)
{
    switch (payaddr.version())
    {
        case payment_address::pubkey_version:
            out_script = build_pubkey_hash_script(payaddr.hash());
            return true;

        case payment_address::script_version:
            out_script = build_script_hash_script(payaddr.hash());
            return true;
    }
    return false;
}

static bool add_output(transaction_type& tx, const std::string& parameter)
{
    transaction_output_type output;
    std::vector<std::string> words;
    split(parameter, words, ":");
    if (words.size() != 2)
    {
        std::cerr << "mktx: Format for output is ADDRESS:VALUE"
            << " or HEXSCRIPT:VALUE."
            << std::endl;
        return false;
    }

    const std::string& output_str = words.front();
    payment_address addr;
    stealth_address stealth;
    script_type rawscript;
    std::string payto;

    if (addr.set_encoded(output_str))
    {
        payto = addr.encoded();
        if (!build_output_script(output.script, addr))
        {
            std::cerr << "mktx: Unsupported address type." << std::endl;
            return false;
        }
    }
    else if (stealth.set_encoded(output_str))
    {
        bool reuse_key = are_flags_set(stealth.options,
            stealth_address::flags::reuse_key);

        // Get our scan and spend pubkeys.
        const ec_point& scan_pubkey = stealth.scan_pubkey;
        BITCOIN_ASSERT_MSG(
            (!reuse_key && stealth.spend_pubkeys.size() == 1) ||
            (reuse_key && stealth.spend_pubkeys.empty()),
            "Multisig stealth addresses not yet supported!");
        BITCOIN_ASSERT_MSG(stealth.prefix.size() == 0,
            "Prefix not supported yet!");
        ec_point spend_pubkey = scan_pubkey;
        if (!reuse_key)
            spend_pubkey = stealth.spend_pubkeys.front();

        // Do stealth stuff.
        ec_secret ephem_secret = generate_random_secret();
        ec_point addr_pubkey = initiate_stealth(
            ephem_secret, scan_pubkey, spend_pubkey);

        // Magic Number?
        // stealth_metadata
        ec_point ephem_pubkey = secret_to_public_key(ephem_secret);
        data_chunk stealth_metadata{{0x06, 0x00, 0x00, 0x00, 0x00}};
        extend_data(stealth_metadata, ephem_pubkey);

        // Add RETURN output.
        transaction_output_type meta_output;
        meta_output.value = 0;
        meta_output.script.push_operation({opcode::return_, data_chunk()});
        meta_output.script.push_operation({opcode::special, stealth_metadata});
        tx.outputs.push_back(meta_output);

        // Generate the address.
        payment_address payaddr;
        set_public_key(payaddr, addr_pubkey);
        payto = payaddr.encoded();

        // Build output script.
        bool success = build_output_script(output.script, payaddr);
        BITCOIN_ASSERT(success);
    }
    else
    {
        try
        {
            rawscript = parse_script(decode_hex(output_str));
        }
        catch (libbitcoin::end_of_stream) 
        {
            std::cerr << "mktx: Bad address or script '" << output_str << "'." << std::endl;
            return false;
        }

        payto = pretty(rawscript);
        output.script = rawscript;
    }

    const std::string& value_str = words[1];
    try
    {
        output.value = boost::lexical_cast<uint64_t>(value_str);
    }
    catch (const boost::bad_lexical_cast&)
    {
        std::cerr << "mktx: Bad VALUE provided." << std::endl;
        return false;
    }

    tx.outputs.push_back(output);
    std::cerr << "Added output sending " << output.value << " Satoshis to "
        << payto << "." << std::endl;
    return true;
}

static bool modify(transaction_type& tx,
    const std::string& action, const std::string& parameter)
{
    if (is_option(action, SX_OPTION_INPUT))
        return add_input(tx, parameter);

    if (is_option(action, SX_OPTION_OUTPUT))
        return add_output(tx, parameter);

    if (is_option(action, SX_OPTION_LOCKTIME))
        return change_locktime(tx, parameter);

    std::cerr << "mktx: Action '" << action << "' doesn't exist." << std::endl;
    return false;
}

console_result tx_encode::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 2))
        return console_result::failure;

    // filename is first arg
    int current_arg = 2;

    // Magic Numbers?
    transaction_type tx;
    tx.version = 1;
    tx.locktime = 0;

    // Create transaction.
    while (two_args_remain(current_arg, argc) && current_arg != argc)
    {
        const std::string action(argv[current_arg]);
        const std::string parameter(argv[current_arg + 1]);
        if (!modify(tx, action, parameter))
            return console_result::failure;

        current_arg += 2;
        BITCOIN_ASSERT(current_arg <= argc);
    }

    // Now serialize transaction.
    data_chunk raw_tx(satoshi_raw_size(tx));
    satoshi_save(tx, raw_tx.begin());

    const std::string filename(get_filename(argc, argv));
    if (filename == SX_STDIN_PATH_SENTINEL)
        std::cout << raw_tx << std::endl;
    else
    {
        std::ofstream outfile(filename, std::ofstream::binary);
        outfile << raw_tx;
    }
    return console_result::okay;
}

