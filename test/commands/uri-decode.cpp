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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(uri_decode__invoke)

#define URI_DECODE_EMPTY \
"uri\n" \
"{\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_ADDRESS \
"uri\n" \
"{\n" \
"    address 1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_STEALTH_ADDRESS \
"uri\n" \
"{\n" \
"    scheme bitcoin\n" \
"    stealth_address\n" \
"    {\n" \
"        encoded hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n" \
"        prefix \"\"\n" \
"        scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
"        signatures 1\n" \
"        spend\n" \
"        {\n" \
"            public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
"        }\n" \
"        testnet false\n" \
"    }\n" \
"}\n"

#define URI_DECODE_AMOUNT \
"uri\n" \
"{\n" \
"    amount 10000120000\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_LABEL \
"uri\n" \
"{\n" \
"    label &=\\\\n#\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_MESSAGE \
"uri\n" \
"{\n" \
"    message \"hello bitcoin\"\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_PAYMENT_REQUEST \
"uri\n" \
"{\n" \
"    r http://example.com?purchase=shoes&user=bob\n" \
"    scheme bitcoin\n" \
"}\n"

#define URI_DECODE_COMPOSITE \
"uri\n" \
"{\n" \
"    amount 10000120000\n" \
"    label &=\\\\n#\n" \
"    message \"hello bitcoin\"\n" \
"    r http://example.com?purchase=shoes&user=bob\n" \
"    scheme bitcoin\n" \
"    stealth_address\n" \
"    {\n" \
"        encoded hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n" \
"        prefix \"\"\n" \
"        scan_public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
"        signatures 1\n" \
"        spend\n" \
"        {\n" \
"            public_key 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006\n" \
"        }\n" \
"        testnet false\n" \
"    }\n" \
"}\n"

BOOST_AUTO_TEST_CASE(uri_decode__invoke__lower_case_scheme_empty_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_EMPTY);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__upper_case_scheme_empty_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "BITCOIN:" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    auto foo = output.str();
    BX_REQUIRE_OUTPUT(URI_DECODE_EMPTY);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__address_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_ADDRESS);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__stealth_address_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_STEALTH_ADDRESS);
}

// only one amount token is allowed on a bitcoin uri
BOOST_AUTO_TEST_CASE(uri_decode__invoke__amount_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?amount=100.0012" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_AMOUNT);
}

// boost::property_tree info serialization is JSON-based, it escapes backslashes
BOOST_AUTO_TEST_CASE(uri_decode__invoke__label_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_format_option({ "info" });
    command.set_uri_argument({ "bitcoin:?label=%26%3D%5Cn%23" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_LABEL);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__message_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?message=hello%20bitcoin" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_MESSAGE);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__payment_request_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?r=http%3A%2F%2Fexample.com%3Fpurchase%3Dshoes%26user%3Dbob" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_PAYMENT_REQUEST);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__stealth_composite_uri__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bItCoIn:hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i?amount=100.0012&label=%26%3D%5Cn%23&message=hello%20bitcoin&r=http%3A%2F%2Fexample.com%3Fpurchase%3Dshoes%26user%3Dbob" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_COMPOSITE);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()