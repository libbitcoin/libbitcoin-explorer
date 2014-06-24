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
#include <boost/test/unit_test.hpp>
#include <sx/sx.hpp>

/********* GENERATED SOURCE CODE, DO NOT EDIT EXCEPT EXPERIMENTALLY **********/

using namespace sx;
using namespace sx::extensions;

BOOST_AUTO_TEST_SUITE(generated__symbol)

BOOST_AUTO_TEST_CASE(generated__symbol__addr__returns_expected_value)
{
    BOOST_REQUIRE(addr::symbol() == std::string("addr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__balance__returns_expected_value)
{
    BOOST_REQUIRE(balance::symbol() == std::string("balance"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BOOST_REQUIRE(help::symbol() == std::string("help"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_addr__returns_expected_value)
{
    BOOST_REQUIRE(stealth_addr::symbol() == std::string("stealth-addr"));
}

BOOST_AUTO_TEST_SUITE_END()
