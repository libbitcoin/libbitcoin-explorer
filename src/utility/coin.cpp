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
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/utility/coin.hpp>
#include <sx/utility/console.hpp>

using namespace bc;

namespace sx {

// TODO: extract localized text.
bool load_tx(transaction_type& tx, const std::string& filename)
{
    std::ostringstream contents;
    if (filename == "-")
    {
        std::istreambuf_iterator<char> first(std::cin), last;
        contents << std::string(first, last);
    }
    else
    {
        std::ifstream infile(filename, std::ifstream::binary);
        if (!infile)
        {
            std::cerr << "showtx: Bad file." << std::endl;
            return false;
        }
        contents << infile.rdbuf();
    }
    auto raw_tx = decode_hex(contents.str());
    try
    {
        satoshi_load(raw_tx.begin(), raw_tx.end(), tx);
    }
    catch (end_of_stream)
    {
        std::cerr << "showtx: Deserializing transaction failed." << std::endl;
        return false;
    }
    return true;
}

// TODO: extract localized text.
bool read_hd_command_args(int argc, char* argv[], bool& is_hard,
    uint32_t& index)
{
    if (argc == 1 || argc > 3)
    {
        std::cerr << "Usage: sx hd-priv [--hard] INDEX" << std::endl;
        return false;
    }

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--hard")
        {
            is_hard = true;
            continue;
        }
        try
        {
            index = boost::lexical_cast<uint32_t>(arg);
        }
        catch (const boost::bad_lexical_cast&)
        {
            std::cerr << "hd-priv: Bad INDEX provided." << std::endl;
            return false;
        }
    }
    return true;
}

// TODO: move to consumer and emit when this is false.
// std::cerr << "Invalid private key." << std::endl;
bool read_private_key(elliptic_curve_key& key, int is_compressed)
{
    return read_private_key(key, read_stdin(), is_compressed);
}

bool read_private_key(elliptic_curve_key& key, const std::string& arg,
    int is_compressed)
{
    bool compressed_flag = true;
    auto secret = decode_hash(arg);
    if (secret == null_hash)
    {
        secret = libwallet::wif_to_secret(arg);
        compressed_flag = libwallet::is_wif_compressed(arg);
    }

    // Overrides for compression
    if (is_compressed == 0)
        compressed_flag = false;
    else if (is_compressed == 1)
        compressed_flag = true;

    return secret != null_hash && key.set_secret(secret, compressed_flag);
}

// TODO: move to consumer and emit when this is false.
// std::cerr << "Invalid public or private key." << std::endl;
bool read_public_or_private_key(elliptic_curve_key& key)
{
    auto arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    auto pubkey = decode_hex(arg);
    return key.set_public_key(pubkey);
}

} // sx
