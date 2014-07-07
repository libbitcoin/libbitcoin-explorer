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
using namespace sx::extension;

BOOST_AUTO_TEST_SUITE(generated__find)

BOOST_AUTO_TEST_CASE(generated__find__addr__returns_object)
{
    BOOST_REQUIRE(find(addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__balance__returns_object)
{
    BOOST_REQUIRE(find(balance::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_decode__returns_object)
{
    BOOST_REQUIRE(find(base58_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58_encode__returns_object)
{
    BOOST_REQUIRE(find(base58_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_decode__returns_object)
{
    BOOST_REQUIRE(find(base58check_decode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__base58check_encode__returns_object)
{
    BOOST_REQUIRE(find(base58check_encode::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_fetch_last_height__returns_object)
{
    BOOST_REQUIRE(find(bci_fetch_last_height::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__bci_history__returns_object)
{
    BOOST_REQUIRE(find(bci_history::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__blke_fetch_transaction__returns_object)
{
    BOOST_REQUIRE(find(blke_fetch_transaction::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__brainwallet__returns_object)
{
    BOOST_REQUIRE(find(brainwallet::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__btc__returns_object)
{
    BOOST_REQUIRE(find(btc::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__decode_addr__returns_object)
{
    BOOST_REQUIRE(find(decode_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add__returns_object)
{
    BOOST_REQUIRE(find(ec_add::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_add_secrets__returns_object)
{
    BOOST_REQUIRE(find(ec_add_secrets::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply__returns_object)
{
    BOOST_REQUIRE(find(ec_multiply::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__ec_multiply_secrets__returns_object)
{
    BOOST_REQUIRE(find(ec_multiply_secrets::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__encode_addr__returns_object)
{
    BOOST_REQUIRE(find(encode_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__help__returns_object)
{
    BOOST_REQUIRE(find(help::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__satoshi__returns_object)
{
    BOOST_REQUIRE(find(satoshi::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__stealth_addr__returns_object)
{
    BOOST_REQUIRE(find(stealth_addr::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__unwrap__returns_object)
{
    BOOST_REQUIRE(find(unwrap::symbol()) != nullptr);
}

BOOST_AUTO_TEST_CASE(generated__find__wrap__returns_object)
{
    BOOST_REQUIRE(find(wrap::symbol()) != nullptr);
}

BOOST_AUTO_TEST_SUITE_END()
