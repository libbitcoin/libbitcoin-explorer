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

namespace sx {

/**
 * Load a transaction from the specified transaction file.
 *
 * @param[in]  tx        The loaded transaction.
 * @param[in]  filename  The path and file name for the transaction file.
 * @return               True if a transaction was loaded.
 */
bool load_tx(bc::transaction_type& tx, const std::string& filename);

/**
 * Parse command line args for hd hardness and index.
 * Searches every argument and returns the last is hard and the last index
 * discovered.
 *
 * @param[in]  argc     The count of arguments in the argument array.
 * @param[in]  argv     The argument array.
 * @param[out] is_hard  The hd is hard parsed value.
 * @param[out] index    The hd index parsed value.
 * @return              True if an is hard and an index have been returned.
 */
bool read_hd_command_args(int argc, char* argv[], bool& is_hard,
    uint32_t& index);

/**
 * Read a private key from the standard input stream.
 *
 * @param[out] key            The read key.
 * @param[in]  is_compressed  Flag indicating whether compression is expected.
 * @return                    True if a key was read.
 */
bool read_private_key(bc::elliptic_curve_key& key, int is_compressed = -1);

/**
 * Read a private key from the standard input stream.
 *
 * @param[out] key            The read key.
 * @param[in]  arg            The argument from which to read the key.
 * @param[in]  is_compressed  Flag indicating whether compression is expected.
 * @return                    True if a key was read.
 */
bool read_private_key(bc::elliptic_curve_key& key, const std::string& arg,
    int is_compressed = -1);

/**
 * Read a public or private key from the standard input stream.
 *
 * @param[out] key  The read key.
 * @return          True if a key was read.
 */
bool read_public_or_private_key(bc::elliptic_curve_key& key);

} // sx

#endif