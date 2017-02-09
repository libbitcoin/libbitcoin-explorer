/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(address_encode__invoke)

// vectors
#define BX_ADDRESS_ENCODE_RIPEMD160_A "b472a266d0bd89c13706a4132ccfb16f7c3b9fcb"

// expectations
#define BX_ADDRESS_ENCODE_ADDRESS_A_MAINNET "1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E"
#define BX_ADDRESS_ENCODE_ADDRESS_A_TESTNET "mwy5FX7MVgDutKYbXBxQG5q7EL6pmhHT58"

BOOST_AUTO_TEST_CASE(address_encode__invoke__mainnet__okay_output)
{
    BX_DECLARE_COMMAND(address_encode);
    command.set_ripemd160_argument({ BX_ADDRESS_ENCODE_RIPEMD160_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_ENCODE_ADDRESS_A_MAINNET "\n");
}

BOOST_AUTO_TEST_CASE(address_encode__invoke__testnet__okay_output)
{
    BX_DECLARE_COMMAND(address_encode);
    command.set_version_option(111);
    command.set_ripemd160_argument({ BX_ADDRESS_ENCODE_RIPEMD160_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_ENCODE_ADDRESS_A_TESTNET "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
