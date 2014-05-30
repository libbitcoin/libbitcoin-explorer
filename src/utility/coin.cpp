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
#include "coin.hpp"
#include "console.hpp"

using namespace bc;

bool load_tx(transaction_type& tx, const std::string& filename)
{
    std::ostringstream contents;
    if (filename == "-")
    {
        std::istreambuf_iterator<char> first(std::cin);
        std::istreambuf_iterator<char> last;
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
    data_chunk raw_tx = decode_hex(contents.str());
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

bool read_private_key(elliptic_curve_key& key, const std::string& arg,
    int is_compressed)
{
    secret_parameter secret = decode_hash(arg);
    bool compressed_flag = true;
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
    if (secret == null_hash || !key.set_secret(secret, compressed_flag))
        return false;
    return true;
}

bool read_private_key(elliptic_curve_key& key, int is_compressed)
{
    if (!read_private_key(key, read_stdin(), is_compressed))
    {
        std::cerr << "Invalid private key." << std::endl;
        return false;
    }
    return true;
}

bool read_public_or_private_key(elliptic_curve_key& key)
{
    std::string arg = read_stdin();
    if (read_private_key(key, arg))
        return true;
    data_chunk pubkey = decode_hex(arg);
    if (key.set_public_key(pubkey))
        return true;
    std::cerr << "Invalid public or private key." << std::endl;
    return false;
}

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

