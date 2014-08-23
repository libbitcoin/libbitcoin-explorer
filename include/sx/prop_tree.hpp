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
#ifndef SX_PROPERTY_TREE_HPP
#define SX_PROPERTY_TREE_HPP

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/header.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/output.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/prefix.hpp>
#include <sx/serializer/stealth.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/serializer/wrapper.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {
    
class address;
class header;
class input;
class output;
class point;
class prefix;
class stealth;
class transaction;
class wrapper;

/**
 * Create a property tree array of property tree elements.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_tree_list(const std::string& name, Values& values);

/**
 * Create a property tree array of value elements.
 * @param      <Values>  The array element type.
 * @param[in]  name      The name of the list elements.
 * @param[in]  values    The enumerable with elements of type Values.
 * @returns              A new property tree containing the list.
 */
template <typename Values>
pt::ptree prop_value_list(const std::string& name, Values& values);

/**
 * Generate a property tree for a block header.
 * @param[in]  header  The header.
 * @return             A property tree.
 */
pt::ptree prop_tree(const header& header);

/**
 * Generate a property tree for a set of headers.
 * @param[in]  headers  The set of headers.
 * @return              A property tree.
 */
pt::ptree prop_tree(const std::vector<header>& headers);

/**
 * Generate a property tree for a history row.
 * @param[in]  row  The history row.
 * @return          A property tree.
 */
pt::ptree prop_tree(const history_row& row);

/**
 * Generate a property tree for a set of history rows.
 *
 * @param[in]  rows  The set of history rows.
 * @return           A property tree.
 */
pt::ptree prop_tree(std::vector<history_row>& rows);

/**
 * Generate a property tree from history rows for an address.
 * @param[in]  history_address  The payment address for the history rows.
 * @param[in]  rows             The set of history rows.
 * @return                      A property tree.
 */
pt::ptree prop_tree(const bc::payment_address& history_address,
    const std::vector<history_row>& rows);

/**
 * Generate a property tree from balance rows for an address.
 * @param[in]  rows             The set of balance rows.
 * @param[in]  balance_address  The payment address for the balance rows.
 * @return                      A property tree.
 */
pt::ptree prop_tree(const std::vector<balance_row>& rows,
    const bc::payment_address& balance_address);

/**
 * Generate a property tree for a transaction input.
 * @param[in]  tx_input  The input.
 * @return               A property tree.
 */
pt::ptree prop_tree(const tx_input_type& tx_input);

/**
 * Generate a property tree for a set of transaction inputs.
 * @param[in]  tx_inputs  The set of transaction inputs.
 * @return                A property tree.
 */
pt::ptree prop_tree(const std::vector<tx_input_type>& tx_inputs);

/**
 * Generate a property tree for an input.
 * @param[in]  input  The input.
 * @return            A property tree.
 */
pt::ptree prop_tree(const sx::serializer::input& input);

/**
 * Generate a property tree for a set of inputs.
 * @param[in]  inputs  The set of inputs.
 * @return             A property tree.
 */
pt::ptree prop_tree(const std::vector<sx::serializer::input>& inputs);

/**
 * Generate a property tree for a transaction output.
 * @param[in]  tx_output  The transaction output.
 * @return                A property tree.
 */
pt::ptree prop_tree(const tx_output_type& tx_output);

/**
 * Generate a property tree for a set of transaction outputs.
 * @param[in]  tx_outputs  The set of transaction outputs.
 * @return                  A property tree.
 */
pt::ptree prop_tree(const std::vector<tx_output_type>& tx_outputs);

/**
 * Generate a property tree for an output.
 * Need a dedicated override here becuase output doesn't cast to 
 * tx_output_type, but instead vector<tx_output_type>.
 * @param[in]  output  The output.
 * @return             A property tree.
 */
pt::ptree prop_tree(const output& output);

/**
 * Generate a property tree for a set of outputs.
 * This must pass the property tree call to the output override so that
 * it can split up the individual transaction outputs.
 * @param[in]  outputs  The set of outputs.
 * @return              A property tree.
 */
pt::ptree prop_tree(const std::vector<output>& outputs);

/**
 * Generate a property tree for a transaction.
 * @param[in]  transaction  The transaction.
 * @return                  A property tree.
 */
pt::ptree prop_tree(const transaction& transaction);

/**
 * Generate a property tree for a set of transactions.
 * @param[in]  transactions  The set of transactions.
 * @return                   A property tree.
 */
pt::ptree prop_tree(const std::vector<transaction>& transactions);

/**
 * Generate a property tree for transaction with extended data.
 * @param[in]  tx          The transaction.
 * @param[in]  block_hash  Theblock_hash of the transaction.
 * @param[in]  prefix      The prefix used to locate the transaction.
 * @return                 A property tree.
 */
pt::ptree prop_tree(const tx_type& tx, const bc::hash_digest& block_hash,
    const prefix& prefix);

/**
 * Generate a property tree for a stealth address.
 * @param[in]  address  The stealth address.
 * @return              A property tree.
 */
pt::ptree prop_tree(const stealth& address);

/**
 * Generate a property tree for a set of stealth addresses.
 * @param[in]  addresses  The set of stealth addresses.
 * @return                A property tree.
 */
pt::ptree prop_tree(const std::vector<stealth>& addresses);

/**
 * Generate a property tree for a stealth metadata row.
 * @param[in]  rows  The stealth row.
 * @return           A property tree.
 */
pt::ptree prop_tree(const bc::blockchain::stealth_row& row);

/**
 * Generate a property tree from stealth metadata rows.
 * @param[in]  rows    The set of stealth rows.
 * @return             A property tree.
 */
pt::ptree prop_tree(const std::vector<bc::blockchain::stealth_row>& rows);

/**
 * Generate a property tree from stealth metadata rows for a prefix.
 * @param[in]  rows    The set of stealth rows.
 * @param[in]  prefix  The stealth prefix.
 * @return             A property tree.
 */
pt::ptree prop_tree(const bc::stealth_prefix& prefix, 
    const std::vector<bc::blockchain::stealth_row>& rows);

/**
 * Generate a property tree for a wrapper.
 * @param[in]  wrapped  A wrapped.
 * @return              A property tree.
 */
pt::ptree prop_tree(const wrapped_data& wrapped);

} // serializer
} // sx

#include <sx/impl/prop_tree.ipp>

#endif