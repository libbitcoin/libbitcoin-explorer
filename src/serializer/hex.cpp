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
#include "precompile.hpp"
#include <sx/serializer/hex.hpp>

#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdint>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <sx/define.hpp>

using namespace bc;
using namespace po;

namespace sx {
namespace serializer {

    hex::hex()
        : value_()
    {
    }

    hex::hex(const std::string& hexcode)
    {
        std::stringstream(hexcode) >> *this;
    }

    hex::hex(const data_chunk& value)
        : value_(value)
    {
    }

    hex::hex(const hex& other)
        : hex(other.value_)
    {
    }

    data_chunk& hex::data()
    {
        return value_;
    }

    hex::operator const data_chunk&() const
    {
        return value_; 
    }

    std::istream& operator>>(std::istream& input, hex& argument)
    {
        std::string hexcode;
        input >> hexcode;

        data_chunk chunk = decode_hex(hexcode);
        if (chunk.empty())
            throw invalid_option_value(hexcode);

        argument.value_.assign(chunk.begin(), chunk.end());
        return input;
    }

    std::ostream& operator<<(std::ostream& output, const hex& argument)
    {
        output << encode_hex(argument.value_);
        return output;
    }

} // sx
} // serializer