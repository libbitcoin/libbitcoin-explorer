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
#ifndef SX_COIN_HPP
#define SX_COIN_HPP

#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

/* NOTE: don't declare 'using namespace foo' in heders. */

namespace sx {

/**
 * Load a satoshi item from the specified file.
 *
 * @param      <TItem>   The type of the item to load.
 * @param[in]  item      The loaded item.
 * @param[in]  filename  The path and file name for the transaction file.
 * @return               True if a transaction was loaded.
 */
template <typename TItem>
bool load_satoshi_item(TItem& item, const std::string& filename)
{
    // TODO: extract localized text.

    std::ostringstream contents;
    if (filename == STDIN_PATH_SENTINEL)
        contents << sx::read_stdin();

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
        satoshi_load(raw_tx.begin(), raw_tx.end(), item);
    }
    catch (end_of_stream)
    {
        std::cerr << "sx: Deserializing item failed." << std::endl;
        return false;
    }
    return true;
}

/**
 * Allocate a byte buffer and fill it with a random bit distribution.
 *
 * @param[in]  size  The byte size of the return buffer.
 * @return           The sized buffer with random bit distribution.
 */
bc::data_chunk random_fill(size_t size);

/**
 * Read address arguments from the specified args and/or input stream.
 *
 * @param[in]  argc          The number of args.
 * @param[in]  argv          The arguments to read.
 * @param[in]  cin           The input stream.
 * @param[out] hex_str       The return string value.
 * @param[out] version_byte  The return byte value.
 */
void read_address_args(const int argc, const char* argv[], std::istream& cin,
    std::string& hex_str, uint8_t& version_byte);

/**
 * Read a private key from STDIN.
 *
 * @param[out] key            The read key.
 * @param[in]  is_compressed  Flag indicating whether compression is expected.
 * @return                    True if a key was read.
 */
bool read_private_key(bc::elliptic_curve_key& key, int is_compressed=-1);

/**
 * Read a private key from STDIN.
 *
 * @param[out] key            The read key.
 * @param[in]  arg            The argument from which to read the key.
 * @param[in]  is_compressed  Flag indicating whether compression is expected,
 *                            -1=unspecified, 0=uncompressed, 1=compressed.
 * @return                    True if a key was read.
 */
bool read_private_key(bc::elliptic_curve_key& key, const std::string& arg,
    int is_compressed=-1);

/**
 * Read a public or private key from STDIN.
 *
 * @param[out] key  The read key.
 * @return          True if a key was read.
 */
bool read_public_or_private_key(bc::elliptic_curve_key& key);

/**
 * Validate the bitcoin checksum of a chunk of binary data.
 *
 * @param[int] data  The data to validate.
 * @return           True if the checksum is valid.
 */
bool validate_checksum(bc::data_chunk& data);

} // sx

#endif