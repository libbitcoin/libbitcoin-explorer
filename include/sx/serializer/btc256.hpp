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
#ifndef BTC256_HPP
#define BTC256_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/hex.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

/**
 * Serialization helper to convert between hex string and hash_digest.
 */
class btc256
{
public:

    /**
     * Constructor.
     */
    btc256()
        : value_()
    {
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  hexcode  The value to initialize with.
     */
    btc256(const std::string& hexcode)
    {
        std::stringstream(hexcode) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    btc256(const bc::hash_digest& value)
        : value_(value)
    {
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    btc256(const btc256& other)
        : btc256(other.value_)
    {
    }

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::hash_digest& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::hash_digest&() const
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
    friend std::istream& operator>>(std::istream& input, btc256& argument)
    {
        std::string hexcode;
        input >> hexcode;

        auto hash = bc::decode_hash(hexcode);
        if (hash == bc::null_hash)
            throw po::invalid_option_value(hexcode);

        std::copy(hash.begin(), hash.end(), argument.value_.begin());
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
        const btc256& argument)
    {
        output << hex(argument.value_);
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::hash_digest value_;
};

} // sx
} // serializer

#endif