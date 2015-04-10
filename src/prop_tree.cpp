/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/prop_tree.hpp>

#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/primitives/address.hpp>
#include <bitcoin/explorer/primitives/base2.hpp>
#include <bitcoin/explorer/primitives/btc256.hpp>
#include <bitcoin/explorer/primitives/ec_public.hpp>
#include <bitcoin/explorer/primitives/header.hpp>
#include <bitcoin/explorer/primitives/input.hpp>
#include <bitcoin/explorer/primitives/output.hpp>
#include <bitcoin/explorer/primitives/point.hpp>
#include <bitcoin/explorer/primitives/script.hpp>
#include <bitcoin/explorer/primitives/transaction.hpp>
#include <bitcoin/explorer/primitives/wrapper.hpp>

using namespace pt;
using namespace bc::client;

namespace libbitcoin {
namespace explorer {
namespace primitives {

// property_tree is very odd in that what one might consider a node or element,
// having a "containing" name cannot be added into another node without
// creating an intervening name/container. so we create uncontained nodes and
// lists which can then be added to a parent node, creating the named container
// on the add.

// Edit with care - text property names trade DRY for readability.
// Edit with care - tests are affected by property ORDER (keep alphabetical).

// headers

ptree prop_list(const header& header)
{
    const chain::block_header& block_header = header;

    ptree tree;
    tree.put("bits", block_header.bits);
    tree.put("hash", btc256(block_header.hash()));
    tree.put("merkle_tree_hash", btc256(block_header.merkle));
    tree.put("nonce", block_header.nonce);
    tree.put("previous_block_hash", btc256(block_header.previous_block_hash));
    tree.put("time_stamp", block_header.timestamp);
    tree.put("version", block_header.version);
    return tree;
}
ptree prop_tree(const header& header)
{
    ptree tree;
    tree.add_child("header", prop_list(header));
    return tree;
}
ptree prop_tree(const std::vector<header>& headers)
{
    ptree tree;
    tree.add_child("headers", prop_tree_list("header", headers));
    return tree;
}

// transfers

ptree prop_list(const history_row& row)
{
    ptree tree;

    tree.put("received.hash", btc256(row.output.hash));

    // missing received.height implies pending
    if (row.output_height != 0)
        tree.put("received.height", row.output_height);

    tree.put("received.index", row.output.index);

    // missing input implies unspent
    if (row.spend.hash != null_hash)
    {
        tree.put("spent.hash", btc256(row.spend.hash));

        // missing input.height implies spend unconfirmed
        if (row.spend_height != 0)
            tree.put("spent.height", row.spend_height);

        tree.put("spent.index", row.spend.index);
    }

    tree.put("value", row.value);
    return tree;
}
ptree prop_tree(const history_row& row)
{
    ptree tree;
    tree.add_child("transfer", prop_list(row));
    return tree;
}
ptree prop_tree(const std::vector<history_row>& rows)
{
    ptree tree;
    tree.add_child("transfers", prop_tree_list("transfer", rows));
    return tree;
}

// balance

ptree prop_list(const std::vector<balance_row>& rows,
    const wallet::payment_address& balance_address)
{
    ptree tree;
    uint64_t total_recieved = 0;
    uint64_t confirmed_balance = 0;
    uint64_t unspent_balance = 0;

    for (const auto& row: rows)
    {
        total_recieved += row.value;

        // spend unconfirmed (or no spend attempted)
        if (row.spend.hash == null_hash)
            unspent_balance += row.value;

        if (row.output_height != 0 &&
            (row.spend.hash == null_hash || row.spend_height == 0))
            confirmed_balance += row.value;
    }

    tree.put("address", address(balance_address));
    tree.put("confirmed", confirmed_balance);
    tree.put("received", total_recieved);
    tree.put("unspent", unspent_balance);
    return tree;
}
ptree prop_tree(const std::vector<balance_row>& rows,
    const wallet::payment_address& balance_address)
{
    ptree tree;
    tree.add_child("balance", prop_list(rows, balance_address));
    return tree;
}

// inputs

ptree prop_list(const tx_input_type& tx_input)
{
    ptree tree;
    wallet::payment_address script_address;
    if (extract(script_address, tx_input.script))
        tree.put("address", address(script_address));

    tree.put("previous_output.hash", btc256(tx_input.previous_output.hash));
    tree.put("previous_output.index", tx_input.previous_output.index);
    tree.put("script", script(tx_input.script).to_string());
    tree.put("sequence", tx_input.sequence);
    return tree;
}
ptree prop_tree(const tx_input_type& tx_input)
{
    ptree tree;
    tree.add_child("input", prop_list(tx_input));
    return tree;
}
ptree prop_tree(const std::vector<tx_input_type>& tx_inputs)
{
    ptree tree;
    tree.add_child("inputs", prop_tree_list("input", tx_inputs));
    return tree;
}

ptree prop_list(const input& input)
{
    const tx_input_type& tx_input = input;
    return prop_list(tx_input);
}
ptree prop_tree(const input& input)
{
    ptree tree;
    tree.add_child("input", prop_list(input));
    return tree;
}
ptree prop_tree(const std::vector<input>& inputs)
{
    auto tx_inputs = cast<input, tx_input_type>(inputs);

    ptree tree;
    tree.add_child("inputs", prop_tree_list("input", tx_inputs));
    return tree;
}

// outputs

ptree prop_list(const tx_output_type& tx_output)
{
    ptree tree;
    wallet::payment_address output_address;
    if (extract(output_address, tx_output.script))
        tree.put("address", address(output_address));

    tree.put("script", script(tx_output.script).to_string());

    // TODO: this will eventually change due to privacy problems, see:
    // lists.dyne.org/lurker/message/20140812.214120.317490ae.en.html
    stealth_info stealth;
    if (extract_stealth_info(stealth, tx_output.script))
    {
        tree.put("stealth.bit_field", stealth.bitfield);
        tree.put("stealth.ephemeral_public_key_hash",
            btc256(stealth.ephem_pubkey_hash));
    }

    tree.put("value", tx_output.value);
    return tree;
}
ptree prop_tree(const tx_output_type& tx_output)
{
    ptree tree;
    tree.add_child("output", prop_list(tx_output));
    return tree;
}
ptree prop_tree(const std::vector<tx_output_type>& tx_outputs)
{
    ptree tree;
    tree.add_child("outputs", prop_tree_list("output", tx_outputs));
    return tree;
}

ptree prop_list(const output& output)
{
    // An output is actually a set of tx_output.
    const std::vector<tx_output_type>& tx_outputs = output;

    ptree tree;
    tree.add_child("outputs", prop_tree_list("output", tx_outputs));
    tree.put("pay_to", output.payto());
    return tree;
}
ptree prop_tree(const output& output)
{
    ptree tree;
    tree.add_child("output", prop_list(output));
    return tree;
}
ptree prop_tree(const std::vector<output>& outputs)
{
    ptree tree;
    tree.add_child("outputs", prop_tree_list("output", outputs));
    return tree;
}

// transactions

ptree prop_list(const transaction& transaction)
{
    const tx_type& tx = transaction;

    ptree tree;
    tree.put("hash", btc256(tx.hash()));
    tree.add_child("inputs", prop_tree_list("input", tx.inputs));
    tree.put("lock_time", tx.locktime);
    tree.add_child("outputs", prop_tree_list("output", tx.outputs));
    tree.put("version", tx.version);
    return tree;
}
ptree prop_tree(const transaction& transaction)
{
    ptree tree;
    tree.add_child("transaction", prop_list(transaction));
    return tree;
}
ptree prop_tree(const std::vector<transaction>& transactions)
{
    ptree tree;
    tree.add_child("transactions",
        prop_tree_list("transaction", transactions));
    return tree;
}

// wrapper

ptree prop_list(const wrapped_data& wrapper)
{
    ptree tree;
    tree.put("checksum", wrapper.checksum);
    tree.put("payload", base16(wrapper.payload));
    tree.put("version", wrapper.version);
    return tree;
}
ptree prop_tree(const wrapped_data& wrapper)
{
    ptree tree;
    tree.add_child("wrapper", prop_list(wrapper));
    return tree;
}

// watch_prefix

ptree prop_list(const tx_type& tx, const hash_digest& block_hash,
    const base2& prefix)
{
    ptree tree;
    tree.add("block", btc256(block_hash));
    tree.add("prefix", prefix);
    tree.add_child("transaction", prop_list(tx));
    return tree;
}
ptree prop_tree(const tx_type& tx, const hash_digest& block_hash,
    const base2& prefix)
{
    ptree tree;
    tree.add_child("watch_prefix", prop_list(tx, block_hash, prefix));
    return tree;
}

// watch_address

ptree prop_list(const tx_type& tx, const hash_digest& block_hash,
    const wallet::payment_address& address)
{
    ptree tree;
    tree.add("block", btc256(block_hash));
    tree.add("address", primitives::address(address));
    tree.add_child("transaction", prop_list(tx));
    return tree;
}
ptree prop_tree(const tx_type& tx, const hash_digest& block_hash,
    const wallet::payment_address& address)
{
    ptree tree;
    tree.add_child("watch_address", prop_list(tx, block_hash, address));
    return tree;
}

// stealth_address

ptree prop_list(const stealth& stealth_address)
{
    // We don't serialize a "reuse key" value as this is strictly an
    // optimization for the purpose of serialization and otherwise complicates
    // understanding of what is actually otherwise very simple behavior.
    // So instead we emit the reused key as one of the spend keys.
    // This means that it is typical to see the same key in scan and spend.

    const wallet::stealth_address& address = stealth_address;
    auto spend_keys = cast<ec_point, ec_public>(address.get_spend_pubkeys());
    auto spend_keys_prop_values = prop_value_list("public_key", spend_keys);

    ptree tree;
    tree.put("encoded", stealth_address);
    tree.put("prefix", address.get_prefix());
    tree.put("scan_public_key", ec_public(address.get_scan_pubkey()));
    tree.put("signatures", address.get_signatures());
    tree.add_child("spend", spend_keys_prop_values);
    tree.put("testnet", address.get_testnet());
    return tree;
}
ptree prop_tree(const stealth& stealth_address)
{
    ptree tree;
    tree.add_child("stealth_address", prop_list(stealth_address));
    return tree;
}

// stealth

ptree prop_list(const client::stealth_row& row)
{
    ptree tree;
    tree.put("ephemeral_public_key", ec_public(row.ephemkey));
    tree.put("paid_address", address(row.address));
    tree.put("transaction_hash", btc256(row.transaction_hash));
    return tree;
}
ptree prop_tree(const client::stealth_row& row)
{
    ptree tree;
    tree.add_child("match", prop_list(row));
    return tree;
}

ptree prop_tree(const std::vector<client::stealth_row>& rows)
{
    ptree tree;
    tree.add_child("stealth", prop_tree_list("match", rows));
    return tree;
}

// metadata

ptree prop_list(const hash_digest& hash, size_t height, size_t index)
{
    ptree tree;
    tree.put("hash", btc256(hash));
    tree.put("height", height);
    tree.put("index", index);
    return tree;
}
ptree prop_tree(const hash_digest& hash, size_t height, size_t index)
{
    ptree tree;
    tree.add_child("metadata", prop_list(hash, height, index));
    return tree;
}

// settings

ptree prop_tree(const settings_list& settings)
{
    ptree list;
    for (const auto& setting: settings)
        list.put(setting.first, setting.second);

    ptree tree;
    tree.add_child("settings", list);
    return tree;
}

// uri

ptree prop_tree(const wallet::uri_parse_result& uri)
{
    ptree uri_props;

    if (uri.address)
        uri_props.put("address", address(uri.address.get()));

    // If both addresses are set stealth will take priority.
    if (uri.stealth)
        uri_props.put("address", stealth(uri.stealth.get()));

    if (uri.amount)
        uri_props.put("amount", uri.amount.get());

    if (uri.label)
        uri_props.put("label", uri.label.get());

    if (uri.message)
        uri_props.put("message", uri.message.get());

    if (uri.r)
        uri_props.put("r", uri.r.get());

    uri_props.put("scheme", "bitcoin");

    ptree tree;
    tree.add_child("uri", uri_props);
    return tree;
}

} // namespace primitives
} // namespace explorer
} // namespace libbitcoin
