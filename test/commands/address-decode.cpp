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
BOOST_AUTO_TEST_SUITE(address_decode__invoke)

// vectors
#define BX_ADDRESS_DECODE_ADDRESS_MAINNET "1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E"
#define BX_ADDRESS_DECODE_ADDRESS_TESTNET "mwy5FX7MVgDutKYbXBxQG5q7EL6pmhHT58"

// expectations
#define BX_ADDRESS_DECODE_MAINNET_INFO \
"wrapper\n" \
"{\n" \
"    checksum 2743498322\n" \
"    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n" \
"    version 0\n" \
"}\n"
/**
#define BX_ADDRESS_DECODE_MAINNET_JSON \
"{\n" \
"    \"wrapper\": {\n" \
"        \"checksum\": \"2743498322\",\n" \
"        \"payload\": \"b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\",\n" \
"        \"version\": \"0\"\n" \
"    }\n" \
"}\n"
*/
#define BX_ADDRESS_DECODE_MAINNET_XML \
"<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
"<wrapper>" \
    "<checksum>2743498322</checksum>" \
    "<payload>b472a266d0bd89c13706a4132ccfb16f7c3b9fcb</payload>" \
    "<version>0</version>" \
"</wrapper>\n"
#define BX_ADDRESS_DECODE_TESTNET_DEFAULT \
"wrapper\n" \
"{\n" \
"    checksum 1475514977\n" \
"    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n" \
"    version 111\n" \
"}\n"

BOOST_AUTO_TEST_CASE(address_decode__invoke__mainnet_info__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::info });
    command.set_payment_address_argument({ BX_ADDRESS_DECODE_ADDRESS_MAINNET });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_MAINNET_INFO);
}

// BOOST is inconsistent across versions regarding pretty printing JSON.
BOOST_AUTO_TEST_CASE(address_decode__invoke__mainnet_json__okay)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::json });
    command.set_payment_address_argument({ BX_ADDRESS_DECODE_ADDRESS_MAINNET });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    // BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_MAINNET_JSON);
}

BOOST_AUTO_TEST_CASE(address_decode__invoke__mainnet_xml__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::xml });
    command.set_payment_address_argument({ BX_ADDRESS_DECODE_ADDRESS_MAINNET });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_MAINNET_XML);
}

BOOST_AUTO_TEST_CASE(address_decode__invoke__testnet_default__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_payment_address_argument({ BX_ADDRESS_DECODE_ADDRESS_TESTNET });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_TESTNET_DEFAULT);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
