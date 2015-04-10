/*
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
#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>
#include <bitcoin/explorer.hpp>


using namespace bc;
using namespace bc::explorer::primitives;

#define ADDRESS_MAINNET_A "15mKKb2eos1hWa6tisdPwwDC1a5J1y9nma"
#define ADDRESS_HD_PRIVATE_KEY_MAINNET_A "xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi"
#define ADDRESS_HD_PUBLIC_KEY_MAINNET_A "xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8"

BOOST_AUTO_TEST_SUITE(primitives)
BOOST_AUTO_TEST_SUITE(primitives__address)

BOOST_AUTO_TEST_CASE(address__constructor__default__does_not_throw)
{
    BOOST_REQUIRE_NO_THROW(address());
}

BOOST_AUTO_TEST_CASE(address__constructor__bogus_string__throws_invalid_option)
{
    //BX_REQUIRE_THROW_INVALID_OPTION_VALUE(address("bogus"));
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_string_cast__round_trips)
{
    const wallet::payment_address pay_address = address(ADDRESS_MAINNET_A);
    BOOST_REQUIRE_EQUAL(pay_address.to_string(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__copy_address_primitives__round_trips)
{
    //BX_SERIALIZE_COPY_ROUND_TRIP(address, ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__payment_address_data__round_trips)
{
    wallet::payment_address pay_address(ADDRESS_MAINNET_A);
    const auto internal_address = address(pay_address).data();
    BOOST_REQUIRE_EQUAL(internal_address.to_string(), ADDRESS_MAINNET_A);
}

#ifndef ENABLE_TESTNET

BOOST_AUTO_TEST_CASE(address__constructor__hd_private_key__converts)
{
    wallet::hd_private_key private_key;
    private_key.set_encoded(ADDRESS_HD_PRIVATE_KEY_MAINNET_A);
    const wallet::payment_address instance = address(private_key);
    BOOST_REQUIRE_EQUAL(instance.to_string(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__hd_public_key__converts)
{
    wallet::hd_public_key public_key;
    public_key.set_encoded(ADDRESS_HD_PUBLIC_KEY_MAINNET_A);
    const wallet::payment_address instance = address(public_key);
    BOOST_REQUIRE_EQUAL(instance.to_string(), ADDRESS_MAINNET_A);
}

#endif

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
