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
#include <bitcoin/explorer/primitives/uri.hpp>

#include <iostream>
#include <string>
#include <cstdint>
#include <boost/program_options.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/prop_tree.hpp>

using namespace po;
using namespace pt;

namespace libbitcoin {
namespace explorer {
namespace primitives {

    uri::uri()
        : value_(), parse_result_()
    {
    }

    uri::uri(const std::string& value)
    {
        std::stringstream(value) >> *this;
    }

    uri::uri(const uri& other)
        : uri(other.value_)
    {
    }

    uri::operator const std::string&() const
    {
        return value_;
    }

    // This will return a default object if not a bitcoin uri.
    uri::operator const uri_parse_result&() const
    {
        return parse_result_;
    }

    std::istream& operator>>(std::istream& input, uri& argument)
    {
        std::string value;
        input >> value;

        // We currently only validate Bitcoin URIs.
        if (starts_with(value, "bitcoin:"))
        {
            if (!uri_parse(value, argument.parse_result_))
                BOOST_THROW_EXCEPTION(invalid_option_value(value));
        }

        argument.value_ = value;
        return input;
    }

    std::ostream& operator<<(std::ostream& output, const uri& argument)
    {
        output << argument.value_;
        return output;
    }

} // namespace explorer
} // namespace primitives
} // namespace libbitcoin
