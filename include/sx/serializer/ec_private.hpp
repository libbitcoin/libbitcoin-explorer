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
#ifndef EC_PRIVATE_HPP
#define EC_PRIVATE_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <sx/define.hpp>
#include <sx/serializer/bitcoin256.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/wif.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and ec_secret.
 */
class ec_private
{
public:

    /**
     * Constructor.
     */
    ec_private()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    ec_private(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    ec_private(const bc::ec_secret& value)
    {
        std::copy(value.begin(), value.end(), value_.begin());
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    ec_private(const libwallet::hd_private_key& value)
        : ec_private(value.private_key()) {}

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    ec_private(const ec_private& other)
        : ec_private(other.value_) {}

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
    operator const bc::ec_secret&() const
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
    friend std::istream& operator>>(std::istream& input, ec_private& argument)
    {
        std::string text;
        input >> text;
        
        bc::ec_secret secret = bitcoin256(text);
        if (!bc::verify_private_key(secret))
            throw po::invalid_option_value(text);

        std::copy(secret.begin(), secret.end(), argument.value_.begin());
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
        const ec_private& argument)
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