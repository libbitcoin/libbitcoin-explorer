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
#ifndef EC_PUBLIC_HPP
#define EC_PUBLIC_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/bytes.hpp>
#include <sx/serializer/ec_private.hpp>
#include <sx/serializer/ec_public.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and ec_point.
 */
class ec_public
{
public:

    /**
     * Constructor.
     */
    ec_public()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    ec_public(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    ec_public(const bc::ec_point& value)
        : value_(value.begin(), value.end()) {}

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    ec_public(const ec_public& other)
        : ec_public(other.value_) {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    ec_public(const libwallet::hd_private_key& value)
        : ec_public(value.public_key()) {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    ec_public(const libwallet::hd_public_key& value)
        : ec_public(value.public_key()) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::ec_point& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::ec_point() const
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
    friend std::istream& operator>>(std::istream& input, ec_public& argument)
    {
        std::string hex;
        input >> hex;

        bc::ec_point point = bytes(hex);
        if (!bc::verify_public_key_fast(point)
            /*|| !bc::verify_public_key(point)*/)
            throw po::invalid_option_value(hex);
        
        argument.value_.assign(point.begin(), point.end());
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
        const ec_public& argument)
    {
        output << bytes(argument.value_);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::ec_point value_;
};

} // sx
} // serializer

#endif