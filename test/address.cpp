/*
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
#include <iostream>
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <sx/sx.hpp>
#include "command.hpp"

SX_USING_NAMESPACES()

// This is a namespace for tests by class/file__method/function.
BOOST_AUTO_TEST_SUITE(address__invoke)

BOOST_AUTO_TEST_CASE(address__constructor__bogus_text__throws_invalid_option_exception)
{
    SX_REQUIRE_INVALID_OPTION_VALUE_EXCEPTION(address("bogus"));
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_text__does_not_throw)
{
    BOOST_REQUIRE_NO_THROW(address("15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma"));
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_payment_address__round_trips)
{
    bc::payment_address payment_address("15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma");
    BOOST_REQUIRE_EQUAL(payment_address.encoded(), address(payment_address).data().encoded());
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_mainnet_hd_private_key__round_trips)
{
    libwallet::hd_private_key private_key;
    private_key.deserialize("xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi");
    const bc::payment_address& instance = address(private_key);
    BOOST_REQUIRE_EQUAL(instance.encoded(), "15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma");
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_hd_mainnet_public_key__round_trips)
{
    libwallet::hd_public_key public_key;
    public_key.deserialize("xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8");
    const bc::payment_address& instance = address(public_key);
    BOOST_REQUIRE_EQUAL(instance.encoded(), "15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma");
}

BOOST_AUTO_TEST_CASE(address__serializers__address__round_trips)
{
    SX_SERIALIZE_COPY_ROUND_TRIP(address, "15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma");
}

BOOST_AUTO_TEST_SUITE_END()