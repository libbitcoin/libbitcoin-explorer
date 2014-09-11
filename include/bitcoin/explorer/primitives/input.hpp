/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#ifndef INPUT_HPP
#define INPUT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Parse two-three tokens into an output point.
 * Throws if the hash digest or index is not valid.
 * 
 * @param[out] input   The out point to populate.
 * @param[in]  tokens  The two-three tokens to parse.
 */
void parse_input(tx_input_type& input,
    const std::vector<std::string>& tokens);

/**
 * Serialization helper stub for tx_input_type.
 */
class input
{
public:

    /**
     * Default constructor.
     */
    input();
    
    /**
     * Initialization constructor.
     * @param[in]  tuple  The value to initialize with.
     */
    input(const std::string& tuple);

    /**
     * Initialization constructor. Only the point is retained.
     * @param[in]  value  The value to initialize with.
     */
    input(const tx_input_type& value);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    input(const input& other);

    /**
     * Initialization constructor. Aspects of the input other than the point
     * are defaulted.
     * @param[in]  value  The value to initialize with.
     */
    input(const input_point& value);

    /**
     * Return a reference to the data member.
     * @return  A reference to the object's internal data.
     */
    tx_input_type& data();

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const tx_input_type&() const;

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
    friend std::istream& operator>>(std::istream& stream, input& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const input& argument);

private:

    /**
     * The state of this object.
     */
    tx_input_type value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif