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
#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between base16/raw script and script_type.
 */
    class script
{
public:

    /**
     * Default constructor.
     */
    script();

    /**
     * Initialization constructor.
     * @param[in]  hexcode  The value to initialize with.
     */
    script(const std::string& hexcode);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    script(const bc::script_type& value);

    /**
     * Initialization constructor.
     * We handle pretty printing internal to the script serializer because
     * we do not use boost program_options to read the words as a single
     * argument. Instead we read a set of string arguments and then explicitly
     * load them here.
     * @param[in]  mnemonics  The mnemonic tokens to initialize with.
     */
    script(const std::vector<std::string>& mnemonics);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    script(const script& other);

    /**
     * Return a pretty-printed copy of the script.
     * See comments on the tokens constructor. We expose this method here for 
     * symmetry with the construction approach.
     * @return  A mnemonic-printed copy of the internal script.
     */
    const std::string mnemonic() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    operator const bc::script_type&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, script& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    friend std::ostream& operator<<(std::ostream& output,
        const script& argument);

private:

    /**
     * The state of this object.
     */
    bc::script_type value_;
};

} // sx
} // serializer

#endif