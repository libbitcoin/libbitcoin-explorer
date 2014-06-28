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

BOOST_AUTO_TEST_CASE(generated__symbol__base58_decode__returns_expected_value)
{
    BOOST_REQUIRE(base58_decode::symbol() == std::string("base58-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58_encode__returns_expected_value)
{
    BOOST_REQUIRE(base58_encode::symbol() == std::string("base58-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_decode__returns_expected_value)
{
    BOOST_REQUIRE(base58check_decode::symbol() == std::string("base58check-decode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__base58check_encode__returns_expected_value)
{
    BOOST_REQUIRE(base58check_encode::symbol() == std::string("base58check-encode"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bci_fetch_last_height__returns_expected_value)
{
    BOOST_REQUIRE(bci_fetch_last_height::symbol() == std::string("bci-fetch-last-height"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__bci_history__returns_expected_value)
{
    BOOST_REQUIRE(bci_history::symbol() == std::string("bci-history"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__blke_fetch_transaction__returns_expected_value)
{
    BOOST_REQUIRE(blke_fetch_transaction::symbol() == std::string("blke-fetch-transaction"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__brainwallet__returns_expected_value)
{
    BOOST_REQUIRE(brainwallet::symbol() == std::string("brainwallet"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__help__returns_expected_value)
{
    BOOST_REQUIRE(help::symbol() == std::string("help"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__stealth_addr__returns_expected_value)
{
    BOOST_REQUIRE(stealth_addr::symbol() == std::string("stealth-addr"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__unwrap__returns_expected_value)
{
    BOOST_REQUIRE(unwrap::symbol() == std::string("unwrap"));
}

BOOST_AUTO_TEST_CASE(generated__symbol__wrap__returns_expected_value)
{
    BOOST_REQUIRE(wrap::symbol() == std::string("wrap"));
}

BOOST_AUTO_TEST_SUITE_END()
