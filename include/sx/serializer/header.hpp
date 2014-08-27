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
#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/base16.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace explorer {
namespace serializer {

/**
 * Serialization helper to convert between serialized and deserialized satoshi 
 * header.
 */
class header
{
public:

    /**
     * Default constructor.
     */
    header();

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The value to initialize with.
     */
    header(const std::string& hexcode);

    ///**
    // * Initialization constructor.
    // * @param[in]  value  The value to initialize with.
    // */
    //header(const bc::data_chunk& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    header(const bc::block_header_type& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    header(const header& other);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    bc::block_header_type& data();

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::block_header_type&() const;

    /**
     * Overload cast to property tree.
     * @return  This object's value cast to a property tree.
     */
    operator const pt::ptree() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, header& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const header& argument);

private:

    /**
     * The state of this object's header data.
     */
    bc::block_header_type value_;
};

} // explorer
} // serializer

#endif