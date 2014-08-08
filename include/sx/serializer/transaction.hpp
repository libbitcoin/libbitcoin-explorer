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
#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <iostream>
#include <string>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between serialized and deserialized satoshi 
 * transaction.
 */
class transaction
{
public:

    /**
     * Constructor.
     */
    transaction()
        : value_()
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  hexcode  The value to initialize with.
     */
    transaction(const std::string& hexcode)
    {
        std::stringstream(hexcode) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    transaction(const bc::data_chunk& value)
        : transaction((const std::string&)hex(value))
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    transaction(const bc::transaction_type& value)
        : value_(value)
    {
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    transaction(const transaction& other)
        : transaction(other.value_)
    {
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::transaction_type& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::transaction_type&() const
    {
        return value_;
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, transaction& argument)
    {
        std::string hexcode;
        input >> hexcode;

        if (!deserialize_satoshi_item(argument.value_, hex(hexcode)))
            throw po::invalid_option_value(hexcode);

        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, 
        const transaction& argument)
    {
        bc::data_chunk bytes;
        serialize_satoshi_item(bytes, argument.value_);
        output << hex(bytes);
        return output;
    }

private:

    /**
     * The state of this object's file data.
     */
    bc::transaction_type value_;
};

/**
 * Generate a property tree for a transaction.
 *
 * @param[in]  transaction  The transaction.
 * @return                  A property tree.
 */
static pt::ptree property_tree(const transaction& transaction)
{
    const bc::transaction_type& tx = transaction;

    pt::ptree tree;
    tree.put("transaction.hash", hex(hash_transaction(tx)));
    tree.put("transaction.version", tx.version);
    tree.put("transaction.locktime", tx.locktime);
    tree.add_child("transaction", property_tree(tx.inputs));
    tree.add_child("transaction", property_tree(tx.outputs));
    return tree;
}

/**
 * Generate a property tree for a set of transactions.
 *
 * @param[in]  transactions  The set of transactions.
 * @return                   A property tree.
 */
static pt::ptree property_tree(const std::vector<transaction>& transactions)
{
    pt::ptree tree;
    for (const auto& transaction: transactions)
        tree.add_child("transactions", property_tree(transaction));

    return tree;
}

} // sx
} // serializer

#endif