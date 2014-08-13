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
#include "precompile.hpp"
#include <sx/prop_tree.hpp>

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/address.hpp>
#include <sx/serializer/header.hpp>
#include <sx/serializer/input.hpp>
#include <sx/serializer/output.hpp>
#include <sx/serializer/point.hpp>
#include <sx/serializer/script.hpp>
#include <sx/serializer/transaction.hpp>
#include <sx/serializer/wrapper.hpp>

using namespace bc;
using namespace libwallet;
using namespace pt;

namespace sx {
namespace serializer {

// Edit with care - text property names trade DRY for readability.

ptree prop_tree(const header& header)
{
    const block_header_type& block_header = header;

    ptree tree;
    tree.put("header.bits", block_header.bits);
    tree.put("header.hash", hex(hash_block_header(block_header)));
    tree.put("header.merkle", hex(block_header.merkle));
    tree.put("header.nonce", block_header.nonce);
    tree.put("header.timestamp", block_header.timestamp);
    tree.put("header.previous", hex(block_header.previous_block_hash));
    tree.put("header.version", block_header.version);
    return tree;
}

ptree prop_tree(const std::vector<header>& headers)
{
    ptree tree;
    for (const auto& header: headers)
        tree.add_child("headers", prop_tree(header));

    return tree;
}

ptree prop_tree(const history_row& row)
{
    ptree tree;
    tree.put("history.value", row.value);
    tree.put("history.output.point", point(row.output));

    // missing => pending
    if (row.output_height != 0)
        tree.put("history.output.height", row.output_height);

    // missing => unspent
    if (row.spend.hash != null_hash)
    {
        tree.put("history.input.point", point(row.spend));

        // missing => pending
        if (row.spend_height != 0)
            tree.put("history.input.height", row.spend_height);
    }

    return tree;
}

ptree prop_tree(const std::vector<history_row>& rows)
{
    ptree tree;
    for (const auto& row: rows)
        tree.add_child("histories", prop_tree(row));

    return tree;
}

ptree prop_tree(const payment_address& history_address,
    const std::vector<history_row>& rows)
{
    ptree tree;
    tree.put("histories.address", address(history_address));
    for (const auto& row: rows)
        tree.add_child("histories", prop_tree(row));

    return tree;
}

ptree prop_tree(const std::vector<balance_row>& rows,
    const payment_address& balance_address)
{
    ptree tree;
    uint64_t value(0);
    uint64_t total_recieved(0);
    uint64_t received_balance(0);
    uint64_t pending_balance(0);

    // We do not assert against the quality of server response values.
    for (const auto& row: rows)
    {
        total_recieved += value;

        if (row.spend.hash == null_hash)
            pending_balance += row.value;

        if (row.output_height != 0 && 
            (row.spend.hash == null_hash || row.spend_height != 0))
            received_balance += row.value;
    }

    tree.put("balance.address", address(balance_address));
    tree.put("balance.paid", total_recieved);
    tree.put("balance.pending", pending_balance);
    tree.put("balance.received", received_balance);

    return tree;
}

ptree prop_tree(const tx_input_type& tx_input)
{
    ptree tree;
    tree.put("input.previous_output", point(tx_input.previous_output));
    tree.put("input.script", script(tx_input.script).mnemonic());
    tree.put("input.sequence", tx_input.sequence);

    payment_address script_address;
    if (extract(script_address, tx_input.script))
        tree.put("input.address", address(script_address));

    return tree;
}

ptree prop_tree(const std::vector<tx_input_type>& tx_inputs)
{
    ptree tree;
    for (const auto& tx_input: tx_inputs)
        tree.add_child("inputs", prop_tree(tx_input));

    return tree;
}

ptree prop_tree(const input& input)
{
    const tx_input_type& tx_input = input;

    ptree tree;
    tree = prop_tree(tx_input);
    return tree;
}

ptree prop_tree(const std::vector<input>& inputs)
{
    ptree tree;
    for (const tx_input_type& tx_input: inputs)
        tree.add_child("inputs", prop_tree(tx_input));

    return tree;
}

ptree prop_tree(const tx_output_type& tx_output)
{
    ptree tree;
    tree.put("output.value", tx_output.value);
    tree.put("output.script", script(tx_output.script).mnemonic());

    payment_address output_address;
    if (extract(output_address, tx_output.script))
        tree.put("output.address", address(output_address));

    // TODO: look into stealth object serialization.
    // This is redundant with output.script yet provided for convenience.
    // However discovery of stealth metadata should not be reliable without
    // a secret key. This impl is based on a too-visible pattern.
    stealth_info stealth;
    if (extract_stealth_info(stealth, tx_output.script))
    {
        tree.put("output.stealth.bitfield", stealth.bitfield);
        tree.put("output.stealth.ephemkey",
            ec_public(stealth.ephem_pubkey));
    }

    return tree;
}

ptree prop_tree(const std::vector<tx_output_type>& tx_outputs)
{
    ptree tree;
    for (const tx_output_type& tx_output: tx_outputs)
        tree.add_child("outputs", prop_tree(tx_output));

    return tree;
}

ptree prop_tree(const output& output)
{
    const std::vector<tx_output_type>& tx_outputs = output;

    ptree tree;
    tree.put("payto", output.payto());
    tree.add_child("", prop_tree(tx_outputs));

    return tree;
}

ptree prop_tree(const std::vector<output>& outputs)
{
    ptree tree;
    for (const auto& output: outputs)
        tree.add_child("outputs", prop_tree(output));

    return tree;
}

ptree prop_tree(const transaction& transaction)
{
    const tx_type& tx = transaction;

    ptree tree;
    tree.put("transaction.hash", hex(hash_transaction(tx)));
    tree.put("transaction.version", tx.version);
    tree.put("transaction.locktime", tx.locktime);
    tree.add_child("transaction", prop_tree(tx.inputs));
    tree.add_child("transaction", prop_tree(tx.outputs));
    return tree;
}

ptree prop_tree(const std::vector<transaction>& transactions)
{
    ptree tree;
    for (const auto& transaction: transactions)
        tree.add_child("transactions", prop_tree(transaction));

    return tree;
}

ptree prop_tree(const wrapped_data& wrapped)
{
    ptree tree;
    tree.put("wrapper.version", wrapped.version);
    tree.put("wrapper.payload", hex(wrapped.payload));
    tree.put("wrapper.checksum", wrapped.checksum);
    return tree;
}

} // serializer
} // sx
