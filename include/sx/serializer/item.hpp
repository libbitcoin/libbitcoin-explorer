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
#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>
#include <sx/utility/utility.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between serialized and deserialized satoshi 
 * items.
 */
template <class SatoshiItem>
class item
{
public:

    /**
     * Constructor.
     */
    item()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    item(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    item(const bc::data_chunk& value)
        : item((const std::string&)hex(value)) {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    item(const SatoshiItem& value)
        : value_(value) {}

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    item(const item& other)
        : item(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    SatoshiItem& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const SatoshiItem&() const
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
    friend std::istream& operator>>(std::istream& input, item& argument)
    {
       hex hexadecimal;
       input >> hexadecimal;

       if (!deserialize_satoshi_item<SatoshiItem>(argument.value_, hexadecimal))
       {
           std::stringstream text;
           text << hexadecimal;
           throw po::invalid_option_value(text.str());
       }

        return input;
    }

    /**
     * Overload stream out.
     *
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output, const item& argument)
    {
        bc::data_chunk bytes;
        serialize_satoshi_item<SatoshiItem>(bytes, argument.value_);

        output << hex(bytes);
        return output;
    }

private:

    /**
     * The state of this object's file data.
     */
    SatoshiItem value_;
};

} // sx
} // serializer

#endif