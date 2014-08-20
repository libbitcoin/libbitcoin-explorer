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
#ifndef SETUP_HPP
#define SETUP_HPP

#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/bitcoin.hpp>
#include <wallet/wallet.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/sx.hpp>

#define SX_USING_NAMESPACES()
using namespace libwallet; \
using namespace bc;
using namespace obelisk; \
using namespace std; \
using namespace sx; \
using namespace sx::extension; \
using namespace sx::serializer;

#define SX_DECLARE_COMMAND(extension) \
    stringstream output, error; \
    extension command

// serializer results
#define SX_SERIALIZE_COPY_ROUND_TRIP(serializer, value) \
    serializer original; \
    stringstream output, input(value); \
    input >> original; \
    serializer copy(original); \
    output << copy; \
    BOOST_REQUIRE_EQUAL(output.str(), value)

// console results
#define SX_REQUIRE_OKAY(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::okay)
#define SX_REQUIRE_FAILURE(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::failure)
#define SX_REQUIRE_INVALID(value) \
    BOOST_REQUIRE_EQUAL(value, console_result::invalid)

// stream results
#define SX_REQUIRE_ERROR(value) \
    BOOST_REQUIRE_EQUAL(error.str(), value)
#define SX_REQUIRE_OUTPUT(value) \
    BOOST_REQUIRE_EQUAL(output.str(), value)

// exceptions
#define SX_REQUIRE_INVALID_OPTION_VALUE_EXCEPTION(expression) \
    BOOST_REQUIRE_THROW(expression, po::invalid_option_value)

#endif