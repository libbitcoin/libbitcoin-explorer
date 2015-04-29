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
#ifndef BX_SCRIPT_HPP
#define BX_SCRIPT_HPP

#include <iostream>
#include <string>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {
namespace primitives {

/**
 * Serialization helper to convert between base16/raw script and script_type.
 */
class script
{
public:

    /**
     * Default constructor.
     */
    BCX_API script();

    /**
     * Initialization constructor.
     * @param[in]  mnemonic  The value to initialize with.
     */
    BCX_API script(const std::string& mnemonic);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    BCX_API script(const script_type& value);

    /**
     * Initialization constructor.
     * @param[in]  value  The value to initialize with.
     */
    BCX_API script(const data_chunk& value);

    /**
     * Initialization constructor.
     * @param[in]  tokens  The mnemonic tokens to initialize with.
     */
    BCX_API script(const std::vector<std::string>& tokens);

    /**
     * Copy constructor.
     * @param[in]  other  The object to copy into self on construct.
     */
    BCX_API script(const script& other);

    /**
     * Serialize the script to bytes according to the wire protocol.
     * @return  The byte serialized copy of the script.
     */
    BCX_API const bc::data_chunk to_data() const;

    /**
     * Return a pretty-printed copy of the script.
     * @return  A mnemonic-printed copy of the internal script.
     */
    BCX_API const std::string to_string() const;

    /**
     * Overload cast to internal type.
     * @return  This object's value cast to internal type.
     */
    BCX_API operator const script_type&() const;

    /**
     * Overload stream in. Throws if input is invalid.
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    BCX_API friend std::istream& operator>>(std::istream& input,
        script& argument);

    /**
     * Overload stream out.
     * @param[in]   output    The output stream to write the value to.
     * @param[out]  argument  The object from which to obtain the value.
     * @return                The output stream reference.
     */
    BCX_API friend std::ostream& operator<<(std::ostream& output,
        const script& argument);

private:

    /**
     * The state of this object.
     */
    script_type value_;
};

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin

#endif