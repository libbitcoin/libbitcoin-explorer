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
#ifndef ADDRESS_HPP
#define ADDRESS_HPP

#include <array>
#include <iostream>
#include <vector>
#include <bitcoin/bitcoin.hpp>
#include <sx/utility/console.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_ADDRESS_EXCEPTION \
    "Invalid payment address."

/**
 * Serialization helper to convert between base58 string and payment_address.
 */
class address
{
public:

    /**
     * Constructor.
     */
    address()
        : value() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  base58  The value to initialize with.
     */
    address(const std::string& base58)
    {
        std::stringstream(base58) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  address  The value to initialize with.
     */
    address(const bc::payment_address& address)
    {
        value.set_encoded(address.encoded());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  argument  The object to copy into self on construct.
     */
    address(const address& argument)
        : value(argument.value) {}

    /**
     * Overload cast to bc::payment_address.
     *
     * @return  This object's value cast to bc::payment_address.
     */
    operator const bc::payment_address() const
    {
        return value; 
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::payment_address& data()
    {
        return value;
    }

    /**
     * Overload stream in. Throws if input is invalid.
     *
     * @param[in]   input     The input stream to read the value from.
     * @param[out]  argument  The object to receive the read value.
     * @return                The input stream reference.
     */
    friend std::istream& operator>>(std::istream& input, address& argument)
    {
        std::string base58;
        input >> base58;

        // TODO: determine how to properly raise error in deserialization.
        if (!argument.value.set_encoded(base58))
            throw std::exception(SX_SERIALIZER_ADDRESS_EXCEPTION);

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
        const address& argument)
    {
        output << argument.value.encoded();
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::payment_address value;
};

} // sx
} // serializer

#endif