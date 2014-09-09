/*
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
#include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(address_decode__invoke)

// vectors
#define BX_ADDRESS_DECODE_ADDRESS_V0 "1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E"
#define BX_ADDRESS_DECODE_ADDRESS_V42 "JBeTK2YUWEFTTQvcqEyQoS3poXKjjc1oEP"

// expectations
#define BX_ADDRESS_DECODE_V0_NATIVE \
    "wrapper\n" \
    "{\n" \
    "    checksum 1476364070\n" \
    "    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n" \
    "    version 0\n" \
    "}\n"
#define BX_ADDRESS_DECODE_V0_INFO \
    "wrapper\n" \
    "{\n" \
    "    checksum 1476364070\n" \
    "    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n" \
    "    version 0\n" \
    "}\n"
/*
#define BX_ADDRESS_DECODE_V0_JSON \
    "{\n" \
    "    \"wrapper\": {\n" \
    "        \"checksum\": \"1476364070\",\n" \
    "        \"payload\": \"b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\",\n" \
    "        \"version\": \"0\"\n" \
    "    }\n" \
    "}\n"
*/
#define BX_ADDRESS_DECODE_V0_XML \
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n" \
    "<wrapper>" \
        "<checksum>1476364070</checksum>" \
        "<payload>b472a266d0bd89c13706a4132ccfb16f7c3b9fcb</payload>" \
        "<version>0</version>" \
    "</wrapper>"
#define BX_ADDRESS_DECODE_V42_DEFAULT \
    "wrapper\n" \
    "{\n" \
    "    checksum 1476364070\n" \
    "    payload b472a266d0bd89c13706a4132ccfb16f7c3b9fcb\n" \
    "    version 42\n" \
    "}\n"

BOOST_AUTO_TEST_CASE(address_decode__invoke__version_0_native__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::native });
    command.set_bitcoin_address_argument({ BX_ADDRESS_DECODE_ADDRESS_V0 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_V0_NATIVE);
}

BOOST_AUTO_TEST_CASE(address_decode__invoke__version_0_info__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::info });
    command.set_bitcoin_address_argument({ BX_ADDRESS_DECODE_ADDRESS_V0 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_V0_INFO);
}

// BOOST is inconsistent across versions regarding pretty printing JSON.
//BOOST_AUTO_TEST_CASE(address_decode__invoke__version_0_json__okay_output)
BOOST_AUTO_TEST_CASE(address_decode__invoke__version_0_json__okay)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::json });
    command.set_bitcoin_address_argument({ BX_ADDRESS_DECODE_ADDRESS_V0 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    // BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_V0_JSON);
}

BOOST_AUTO_TEST_CASE(address_decode__invoke__version_0_xml__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_format_option({ encoding_engine::xml });
    command.set_bitcoin_address_argument({ BX_ADDRESS_DECODE_ADDRESS_V0 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_V0_XML);
}

BOOST_AUTO_TEST_CASE(address_decode__invoke__version_42_default__okay_output)
{
    BX_DECLARE_COMMAND(address_decode);
    command.set_bitcoin_address_argument({ BX_ADDRESS_DECODE_ADDRESS_V42 });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_ADDRESS_DECODE_V42_DEFAULT);
}

BOOST_AUTO_TEST_SUITE_END()
