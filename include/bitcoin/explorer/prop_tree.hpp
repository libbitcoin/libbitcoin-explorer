/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
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
#ifndef BX_PROPERTY_TREE_HPP
#define BX_PROPERTY_TREE_HPP

#include <map>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/header.hpp>
#include <bitcoin/explorer/config/input.hpp>
#include <bitcoin/explorer/config/output.hpp>
#include <bitcoin/explorer/config/point.hpp>
#include <bitcoin/explorer/config/transaction.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace config {
    
class base2;
class header;
class input;
class output;
class transaction;
class wrapper;

/**
 * A tuple to represent settings and serialized values.
 */
typedef std::map<std::string, std::string> settings_list;

/**
 * Create a property tree array of property tree elements.
 * The child elements of Value contain no arrays.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_tree_list(const std::string& name, const Values& values,
    bool json);

/**
 * Create a property tree array of property tree elements.
 * The child elements of Value contain arrays.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_tree_list_of_lists(const std::string& name,
    const Values& values, bool json);

/**
 * Create a property tree array of value elements.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @param[in]  json      Use json array formating.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_value_list(const std::string& name, const Values& values,
    bool json);

/**
 * Generate a property list for a block header.
 * @param[in]  header  The header.
 * @return             A property list.
 */
BCX_API pt::ptree prop_list(const header& header);

/**
 * Generate a property tree for a block header.
 * @param[in]  header  The header.
 * @return             A property tree.
 */
BCX_API pt::ptree prop_tree(const header& header);

/**
 * Generate a property tree for a set of headers.
 * @param[in]  headers  The set of headers.
 * @return              A property tree.
 */
BCX_API pt::ptree prop_tree(const std::vector<header>& headers);

/**
* Generate a property list for a history row.
* @param[in]  row  The history row.
* @return          A property list.
*/
BCX_API pt::ptree prop_list(const chain::history& row);

/**
 * Generate a property tree for a history row.
 * @param[in]  row  The history row.
 * @return          A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::history& row);

/**
 * Generate a property tree for a set of history rows.
 *
 * @param[in]  rows  The set of history rows.
 * @param[in]  json  Use json array formatting.
 * @return           A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::history::list& rows, bool json);

/**
 * Generate a property list from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const chain::history::list& rows,
    const wallet::payment_address& balance_address);

/**
 * Generate a property tree from balance rows for an address.
 * This doesn't require array formatting because it summarizes the rows.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::history::list& rows,
    const wallet::payment_address& balance_address);

/**
 * Generate a property list for a transaction input.
 * @param[in]  tx_input  The input.
 * @return               A property list.
 */
BCX_API pt::ptree prop_list(const tx_input_type& tx_input);

/**
 * Generate a property tree for a transaction input.
 * @param[in]  tx_input  The input.
 * @return               A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_input_type& tx_input);

/**
 * Generate a property tree for a set of transaction inputs.
 * @param[in]  tx_inputs  The set of transaction inputs.
 * @param[in]  json       Use json array formatting.
 * @return                A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_input_type::list& tx_inputs, bool json);

/**
 * Generate a property list for an input.
 * @param[in]  input  The input.
 * @return            A property list.
 */
BCX_API pt::ptree prop_list(const explorer::config::input& input);

/**
 * Generate a property tree for an input.
 * @param[in]  input  The input.
 * @return            A property tree.
 */
BCX_API pt::ptree prop_tree(const explorer::config::input& input);

/**
 * Generate a property tree for a set of inputs.
 * @param[in]  inputs  The set of inputs.
 * @param[in]  json    Use json array formatting.
 * @return             A property tree.
 */
BCX_API pt::ptree prop_tree(
    const std::vector<explorer::config::input>& inputs, bool json);

/**
 * Generate a property list for a transaction output.
 * @param[in]  tx_output  The transaction output.
 * @return                A property list.
 */
BCX_API pt::ptree prop_list(const tx_output_type& tx_output);

/**
 * Generate a property tree for a transaction output.
 * @param[in]  tx_output  The transaction output.
 * @return                A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_output_type& tx_output);

/**
 * Generate a property tree for a set of transaction outputs.
 * @param[in]  tx_outputs  The set of transaction outputs.
 * @param[in]  json        Use json array formatting.
 * @return                 A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_output_type::list& tx_outputs,
    bool json);

/**
 * Generate a property list for a point.
 * @param[in]  p          The point.
 * @return                A property list.
 */
BCX_API pt::ptree prop_list(const chain::point& point);

/**
 * Generate a property tree for a set of points.
 * @param[in]  points  The set of points.
 * @param[in]  json        Use json array formatting.
 * @return                 A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::point::list& points, bool json);

/**
 * Generate a property tree for a points_info.
 * @param[in]  p_info       The points_info.
 * @param[in]  json         Use json array formatting.
 * @return                  A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::points_info& points_info, bool json);

/**
 * Generate a property list for a transaction.
 * @param[in]  transaction  The transaction.
 * @param[in]  json         Use json array formatting.
 * @return                  A property list.
 */
BCX_API pt::ptree prop_list(const transaction& transaction, bool json);

/**
 * Generate a property tree for a transaction.
 * @param[in]  transaction  The transaction.
 * @param[in]  json         Use json array formatting.
 * @return                  A property tree.
 */
BCX_API pt::ptree prop_tree(const transaction& transaction, bool json);

/**
 * Generate a property tree for a set of transactions.
 * @param[in]  transactions  The set of transactions.
 * @param[in]  json          Use json array formatting.
 * @return                   A property tree.
 */
BCX_API pt::ptree prop_tree(const std::vector<transaction>& transactions,
    bool json);

/**
 * Generate a property list for a wrapper.
 * @param[in]  wrapper  The wrapper instance.
 * @return              A property list.
 */
BCX_API pt::ptree prop_list(const wallet::wrapped_data& wrapper);

/**
 * Generate a property tree for a wrapper.
 * @param[in]  wrapper  The wrapper instance.
 * @return              A property tree.
 */
BCX_API pt::ptree prop_tree(const wallet::wrapped_data& wrapper);

///**
// * Generate a property list for transaction with extended data.
// * @param[in]  tx          The transaction.
// * @param[in]  block_hash  The block_hash of the transaction.
// * @param[in]  filter      The filter used to locate the transaction.
// * @param[in]  json        Use json array formatting.
// * @return                 A property list.
// */
//BCX_API pt::ptree prop_list(const tx_type& tx, const hash_digest& block_hash,
//    const base2& filter, bool json);
//
///**
// * Generate a property tree for transaction with extended data.
// * @param[in]  tx          The transaction.
// * @param[in]  block_hash  The block_hash of the transaction.
// * @param[in]  filter      The filter used to locate the transaction.
// * @param[in]  json        Use json array formatting.
// * @return                 A property tree.
// */
//BCX_API pt::ptree prop_tree(const tx_type& tx, const hash_digest& block_hash,
//    const base2& filter, bool json);

/**
 * Generate a property list for transaction with extended data.
 * @param[in]  tx          The transaction.
 * @param[in]  block_hash  The block_hash of the transaction.
 * @param[in]  address     The address used to locate the transaction.
 * @param[in]  json        Use json array formatting.
 * @return                 A property list.
 */
BCX_API pt::ptree prop_list(const tx_type& tx, const hash_digest& block_hash,
    const wallet::payment_address& address, bool json);

/**
 * Generate a property tree for transaction with extended data.
 * @param[in]  tx          The transaction.
 * @param[in]  block_hash  The block_hash of the transaction.
 * @param[in]  address     The address used to locate the transaction.
 * @param[in]  json        Use json array formatting.
 * @return                 A property tree.
 */
BCX_API pt::ptree prop_tree(const tx_type& tx, const hash_digest& block_hash,
    const wallet::payment_address& address, bool json);

/**
 * Generate a property list for a stealth address.
 * @param[in]  stealth_address  The stealth address.
 * @param[in]  json             Use json array formatting.
 * @return                      A property list.
 */
BCX_API pt::ptree prop_list(const wallet::stealth_address& stealth, bool json);

/**
 * Generate a property tree for a stealth address.
 * @param[in]  stealth_address  The stealth address.
 * @param[in]  json             Use json array formatting.
 * @return                      A property tree.
 */
BCX_API pt::ptree prop_tree(const wallet::stealth_address& stealth, bool json);

/**
 * Generate a property list for a stealth metadata row.
 * @param[in]  rows  The stealth row.
 * @return           A property list.
 */
BCX_API pt::ptree prop_list(const chain::stealth& row);

/**
 * Generate a property tree for a stealth metadata row.
 * @param[in]  rows  The stealth row.
 * @return           A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::stealth& row);

/**
 * Generate a property tree from stealth metadata rows.
 * @param[in]  rows    The set of stealth rows.
 * @param[in]  json    Use json array formatting.
 * @return             A property tree.
 */
BCX_API pt::ptree prop_tree(const chain::stealth::list& rows, bool json);

/**
 * Create a property list for the fetch-tx-index command.
 * @param[in]  hash    The block hash.
 * @param[in]  height  The block height.
 * @param[in]  index   The tx index.
 * @returns            A new property list containing the list.
 */
BCX_API pt::ptree prop_list(const bc::hash_digest& hash, size_t height,
    size_t index);

/**
 * Create a property tree for the fetch-tx-index command.
 * @param[in]  hash    The block hash.
 * @param[in]  height  The block height.
 * @param[in]  index   The tx index.
 * @returns            A new property tree containing the list.
 */
BCX_API pt::ptree prop_tree(const bc::hash_digest& hash, size_t height,
    size_t index);

/**
 * Create a property tree for the settings command.
 * @param[in]  settings   The list of settings.
 * @returns               A new property tree containing the settings.
 */
BCX_API pt::ptree prop_tree(const settings_list& settings);

/**
 * Create a property tree for a parsed bitcoin uri.
 * @param[in]  uri   The parsed uri.
 * @returns          A new property tree containing the settings.
 */
BCX_API pt::ptree prop_tree(const wallet::bitcoin_uri& uri);

} // namespace config
} // namespace explorer
} // namespace libbitcoin

#include <bitcoin/explorer/impl/prop_tree.ipp>

#endif
