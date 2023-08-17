/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef BX_PROPERTY_TREE_HPP
#define BX_PROPERTY_TREE_HPP

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/system.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

/**
* Generate a property list for a history row.
* @param[in]  row  The history row.
* @return          A property list.
*/
BCX_API pt::ptree prop_list(const client::history& row);

/**
 * Generate a property tree for a history row.
 * @param[in]  row  The history row.
 * @return          A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history& row);

/**
 * Generate a property tree for a set of history rows.
 *
 * @param[in]  rows  The set of history rows.
 * @param[in]  json  Use json array formatting.
 * @return           A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows, bool json);

/**
 * Generate a property list from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The script hash for the balance rows.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const client::history::list& rows,
    const system::hash_digest& script_hash);

/**
 * Generate a property tree from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The script hash for the balance rows.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows,
    const system::hash_digest& script_hash);

/**
 * Generate a property list from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const client::history::list& rows,
    const system::wallet::payment_address& balance_address);

/**
 * Generate a property tree from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const client::history::list& rows,
    const system::wallet::payment_address& balance_address);

/**
 * Generate a property tree for a set of transaction inputs.
 * @param[in]  tx_inputs  The set of transaction inputs.
 * @param[in]  json       Use json array formatting.
 * @return                A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_input_type::list& tx_inputs, bool json);

/**
 * Generate a property tree for a set of transaction outputs.
 * @param[in]  tx_outputs  The set of transaction outputs.
 * @param[in]  json        Use json array formatting.
 * @return                 A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_output_type::list& tx_outputs,
    bool json);

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#include <bitcoin/explorer/impl/prop_tree.ipp>

#endif
