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
#ifndef SX_COIN_HPP
#define SX_COIN_HPP

#include <fstream>
#include <iostream>
#include <stdint.h>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/utility/console.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {

/**
 * Type for definiing lists of payment addresses. 
 */
typedef std::vector<bc::payment_address> payaddr_list;

/**
 * Key compression states (3-state boolean). 
 */
enum key_compression : uint8_t
{ 
    unspecified, 
    on, 
    off 
};

/**
 * Load a satoshi item from the specified file.
 *
 * @param      <Item>    The type of the item to load.
 * @param[out] item      The loaded item.
 * @param[in]  filename  The path and file name for the transaction file.
 * @param[in]  stream    The stream to load from, if the file is "-".
 * @return               True if a transaction was loaded.
 */
template <typename Item>
bool load_satoshi_item(Item& item, const std::string& filename,
    std::istream& stream)
{
    std::ostringstream contents;
    if (filename == SX_STDIN_PATH_SENTINEL)
        contents << sx::read_stream(stream);
    else
    {
        std::ifstream infile(filename, std::ifstream::binary);
        if (!infile)
            return false;

        contents << infile.rdbuf();
    }
    auto raw_tx = bc::decode_hex(contents.str());
    try
    {
        satoshi_load(raw_tx.begin(), raw_tx.end(), item);
    }
    catch (bc::end_of_stream)
    {
        return false;
    }
    return true;
}

/**
 * Generate a random secret using the default random engine.
 *
 * @return  The new secret.
 */
bc::ec_secret random_secret();

/**
 * Allocate a byte buffer and fill it with a random bit distribution.
 *
 * @param[in]  size  The byte size of the return buffer.
 * @return           The sized buffer with random bit distribution.
 */
bc::data_chunk random_fill(size_t size);

/**
 * Read a set of payment addresses from the specified vector.
 *
 * @param[in]  addresses  The payment addresses to read.
 * @param[out] payaddrs   The payment addresses read.
 * return                 True if there was no payment address parse error.
 */
bool read_addresses(std::vector<std::string> addresses, 
    sx::payaddr_list& payaddrs);

/**
 * Validate the bitcoin checksum of a chunk of binary data.
 *
 * @param[int] data  The data to validate.
 * @return           True if the checksum is valid.
 */
bool validate_checksum(const bc::data_chunk& data);

} // sx

#endif
