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
#ifndef SECRET_HPP
#define SECRET_HPP

#include <array>
#include <iostream>
#include <stdint.h>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_SECRET_EXCEPTION \
    "Elliptic curve secret must be 32 bytes."

/**
 * Serialization helper to convert between hex string and ec_secret.
 */
class secret
{
public:

    /**
     * Constructor.
     */
    secret()
        : value() {}

    /**
     * Initialization counstructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    secret(const std::string& hex)
    {
        auto chunk = bc::decode_hex(hex);
        if (!vector_to_array(chunk, value))
            throw std::exception(SX_SERIALIZER_SECRET_EXCEPTION);
    }

    /**
     * Copy counstructor.
     *
     * @param[in]  argument  The object to copy into self on construct.
     */
    secret(const secret& argument)
        : value(argument.value) {}

    /**
     * Overload cast to bc::ec_secret.
     *
     * @return  This object's value cast to bc::ec_secret.
     */
    operator bc::ec_secret() const
    {
        return value; 
    }

    /**
     * Overload stream in. If input is invalid sets no bytes in argument.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, secret& argument)
    {
        std::string hex;
        input >> hex;
        auto chunk = bc::decode_hex(hex);

        if (!vector_to_array(chunk, argument.value))
            throw std::exception(SX_SERIALIZER_SECRET_EXCEPTION);

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
        const secret& argument)
    {
        output << bc::encode_hex(argument.value);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::ec_secret value;
};

} // sx
} // serializer

#endif