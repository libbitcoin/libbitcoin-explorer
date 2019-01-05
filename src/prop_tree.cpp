/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
using namespace bc::system;
using namespace bc::system::config;
using namespace bc::system::machine;
using namespace bc::system::wallet;

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

} // namespace config
} // namespace explorer
} // namespace libbitcoin
