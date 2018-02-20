/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

#include <bitcoin/explorer/prop_tree.hpp>

#include <cstdint>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/config/wrapper.hpp>

namespace libbitcoin {
namespace explorer {
namespace config {

using namespace pt;
using namespace bc::client;
using namespace bc::config;
using namespace bc::machine;
using namespace bc::wallet;

// property_tree is very odd in that what one might consider a node or element,
// having a "containing" name cannot be added into another node without
// creating an intervening name/container. so we create uncontained nodes and
// lists which can then be added to a parent node, creating the named container
// on the add.

// Edit with care - text property names trade DRY for readability.
// Edit with care - tests are affected by property ORDER (keep alphabetical).

// transfers

ptree prop_list(const client::history& row)
{
    ptree tree;

    // missing output implies output cut off by server's history threshold
    if (row.output.hash() != null_hash)
    {
        tree.put("received.hash", hash256(row.output.hash()));

        // zeroized received.height implies output unconfirmed (in mempool)
        if (row.output_height != 0)
            tree.put("received.height", row.output_height);

        tree.put("received.index", row.output.index());
    }

    // missing input implies unspent
    if (row.spend.hash() != null_hash)
    {
        tree.put("spent.hash", hash256(row.spend.hash()));

        // zeroized input.height implies spend unconfirmed (in mempool)
        if (row.spend_height != 0)
            tree.put("spent.height", row.spend_height);

        tree.put("spent.index", row.spend.index());
    }

    tree.put("value", row.value);
    return tree;
}

ptree prop_tree(const client::history& row)
{
    ptree tree;
    tree.add_child("transfer", prop_list(row));
    return tree;
}

ptree prop_tree(const client::history::list& rows, bool json)
{
    ptree tree;
    tree.add_child("transfers", prop_tree_list("transfer", rows, json));
    return tree;
}

// balance

ptree prop_list(const client::history::list& rows,
    const payment_address& balance_address)
{
    ptree tree;
    uint64_t spent = 0;
    uint64_t received = 0;

    for (const auto& row: rows)
    {
        received = ceiling_add(received, row.value);

        if (row.spend.hash() != null_hash)
            spent = ceiling_add(spent, row.value);
    }

    tree.put("address", balance_address);
    tree.put("received", received);
    tree.put("spent", spent);
    return tree;
}

ptree prop_tree(const client::history::list& rows,
    const payment_address& balance_address)
{
    ptree tree;
    tree.add_child("balance", prop_list(rows, balance_address));
    return tree;
}

// wrapper

ptree prop_list(const wallet::wrapped_data& wrapper)
{
    ptree tree;
    tree.put("checksum", wrapper.checksum);
    tree.put("payload", base16(wrapper.payload));
    tree.put("version", wrapper.version);
    return tree;
}

ptree prop_tree(const wallet::wrapped_data& wrapper)
{
    ptree tree;
    tree.add_child("wrapper", prop_list(wrapper));
    return tree;
}

// stealth_address

ptree prop_list(const stealth_address& stealth, bool json)
{
    // We don't serialize a "reuse key" value as this is strictly an
    // optimization for the purpose of serialization and otherwise complicates
    // understanding of what is actually otherwise very simple behavior.
    // So instead we emit the reused key as one of the spend keys.
    // This means that it is typical to see the same key in scan and spend.

    const auto spends = cast<ec_compressed, ec_public>(stealth.spend_keys());
    const auto spends_values = prop_value_list("public_key", spends, json);

    ptree tree;
    tree.put("encoded", stealth);
    tree.put("filter", stealth.filter());
    tree.put("scan_public_key", ec_public(stealth.scan_key()));
    tree.put("signatures", stealth.signatures());
    tree.add_child("spends", spends_values);
    tree.put("version", stealth.version());
    return tree;
}

ptree prop_tree(const stealth_address& stealth, bool json)
{
    ptree tree;
    tree.add_child("stealth_address", prop_list(stealth, json));
    return tree;
}

// stealth

ptree prop_list(const client::stealth& row)
{
    ptree tree;
    tree.put("ephemeral_public_key", ec_public(row.ephemeral_public_key));
    tree.put("public_key_hash", hash160(row.public_key_hash));
    tree.put("transaction_hash", hash256(row.transaction_hash));
    return tree;
}

ptree prop_tree(const client::stealth& row)
{
    ptree tree;
    tree.add_child("match", prop_list(row));
    return tree;
}

ptree prop_tree(const client::stealth::list& rows, bool json)
{
    ptree tree;
    tree.add_child("stealth", prop_tree_list("match", rows, json));
    return tree;
}

// metadata

ptree prop_list(const hash_digest& hash, size_t height, size_t index)
{
    ptree tree;
    tree.put("hash", hash256(hash));
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

ptree prop_tree(const bitcoin_uri& uri)
{
    ptree uri_props;

    if (!uri.address().empty())
        uri_props.put("address", uri.address());

    if (uri.amount() != 0)
        uri_props.put("amount", uri.amount());

    if (!uri.label().empty())
        uri_props.put("label", uri.label());

    if (!uri.message().empty())
        uri_props.put("message", uri.message());

    if (!uri.r().empty())
        uri_props.put("r", uri.r());

    uri_props.put("scheme", "bitcoin");

    ptree tree;
    tree.add_child("uri", uri_props);
    return tree;
}

} // namespace config
} // namespace explorer
} // namespace libbitcoin
