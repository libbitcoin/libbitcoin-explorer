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

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/serializer/bitcoin256.hpp>
#include <sx/serializer/wif.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_SECRET_EXCEPTION \
    "Invalid elliptic curve secret."

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
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    secret(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    secret(const bc::ec_secret& value)
    {
        std::copy(value.begin(), value.end(), value_.begin());
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    secret(const secret& other)
        : secret(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::ec_secret& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::ec_secret() const
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
    friend std::istream& operator>>(std::istream& input, secret& argument)
    {
        std::string text;
        input >> text;
        bc::ec_secret value;

        try
        {
            // First try to read as WIF secret.
            value = wif(text);
        }
        catch (po::invalid_option_value)
        {
            // Next try to read as hash secret.
            value = bitcoin256(text);

            if (!bc::verify_private_key(value))
                throw po::invalid_option_value(SX_SERIALIZER_SECRET_EXCEPTION);
        }

        std::copy(value.begin(), value.end(), argument.value_.begin());
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
        output << bitcoin256(argument.value_);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::ec_secret value_;
};

} // sx
} // serializer

#endif