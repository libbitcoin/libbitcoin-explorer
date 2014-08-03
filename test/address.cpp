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
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(address_serializer)

BOOST_AUTO_TEST_CASE(address__constructor__default__does_not_throw)
{
    BOOST_REQUIRE_NO_THROW(address());
}

BOOST_AUTO_TEST_CASE(address__constructor__bogus_string__throws_invalid_option)
{
    SX_REQUIRE_INVALID_OPTION_VALUE_EXCEPTION(address("bogus"));
}

BOOST_AUTO_TEST_CASE(address__constructor__valid_string__cast_round_trips)
{
    const payment_address& payment_address = address(ADDRESS_MAINNET_A);
    BOOST_REQUIRE_EQUAL(payment_address.encoded(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__copy_address__serializer_round_trips)
{
    SX_SERIALIZE_COPY_ROUND_TRIP(address, ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__payment_address__data_round_trips)
{
    payment_address pay_address(ADDRESS_MAINNET_A);
    const auto& internal_address = address(pay_address).data();
    BOOST_REQUIRE_EQUAL(internal_address.encoded(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__hd_private_key__converts)
{
    hd_private_key private_key;
    private_key.deserialize(HD_PRIVATE_KEY_MAINNET_A);
    const payment_address& instance = address(private_key);
    BOOST_REQUIRE_EQUAL(instance.encoded(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_CASE(address__constructor__hd_public_key__converts)
{
    hd_public_key public_key;
    public_key.deserialize(HD_PUBLIC_KEY_MAINNET_A);
    const payment_address& instance = address(public_key);
    BOOST_REQUIRE_EQUAL(instance.encoded(), ADDRESS_MAINNET_A);
}

BOOST_AUTO_TEST_SUITE_END()