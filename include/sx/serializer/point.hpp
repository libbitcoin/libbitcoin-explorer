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
#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>
#include <sx/serializer/btc256.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace sx {
namespace serializer {

#define SX_SERIALIZER_POINT_DELIMITER ":"

/**
 * Serialization helper to convert between hex string and input_point and
 * output_point. These points should not be confused with points on a curve.
 */
class point
{
public:

    /**
     * Constructor.
     */
    point()
        : value_() {}

    /**
     * Initialization constructor.
     * 
     * @param[in]  hex  The value to initialize with.
     */
    point(const std::string& hex)
    {
        std::stringstream(hex) >> *this;
    }

    /**
     * Initialization constructor.
     * 
     * @param[in]  value  The value to initialize with.
     */
    point(const bc::output_point& value)
        : value_(value)
    {
        value_.index = value.index;
    }

    /**
     * Copy constructor.
     *
     * @param[in]  other  The object to copy into self on construct.
     */
    point(const point& other)
        : point(other.value_) {}

    /**
     * Return a reference to the data member.
     *
     * @return  A reference to the object's internal data.
     */
    bc::output_point& data()
    {
        return value_;
    }

    /**
     * Overload cast to internal type.
     *
     * @return  This object's value cast to internal type.
     */
    operator const bc::output_point&() const
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
    friend std::istream& operator>>(std::istream& input, point& argument)
    {
        std::string text;
        input >> text;

        // Note: there is no bc::uncat_point()
        std::vector<std::string> tokens;
        split(text, tokens, SX_SERIALIZER_POINT_DELIMITER);
        if (tokens.size() != 2)
            throw po::invalid_option_value(text);

//        parse(argument.value_.index, tokens[1]);
        bc::hash_digest hash = btc256(tokens[0]);

        std::copy(hash.begin(), hash.end(), argument.value_.hash.begin());
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
        const point& argument)
    {
        // See bc::concat_point()
        output << btc256(argument.value_.hash) <<
            SX_SERIALIZER_POINT_DELIMITER << argument.value_.index;
        return output;
    }

private:

    /**
     * The state of this object.
     */
    bc::output_point value_;
};

} // sx
} // serializer

#endif