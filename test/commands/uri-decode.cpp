/**
 * Copyright (c) 2011-2023 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(uri_decode__invoke)

#define URI_DECODE_BIP21_ADDRESS "{\"uri\":{\"address\":\"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_BIP21_ADDRESS_LABEL "{\"uri\":{\"address\":\"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\",\"label\":\"Luke-Jr\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_BIP21_ADDRESS_AMOUNT_LABEL "{\"uri\":{\"address\":\"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\",\"amount\":2030000000,\"label\":\"Luke-Jr\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_BIP21_ADDRESS_AMOUNT_LABEL_MESSAGE "{\"uri\":{\"address\":\"1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\",\"amount\":5000000000,\"label\":\"Luke-Jr\",\"message\":\"Donation for project xyz\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_EMPTY "{\"uri\":{\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_ADDRESS "{\"uri\":{\"address\":\"1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_AMOUNT "{\"uri\":{\"amount\":10000120000,\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_LABEL "{\"uri\":{\"label\":\"&=\\\\n#\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_MESSAGE "{\"uri\":{\"message\":\"hello bitcoin\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_PAYMENT_REQUEST "{\"uri\":{\"r\":\"http://example.com?purchase=shoes&user=bob\",\"scheme\":\"bitcoin\"}}\n"

#define URI_DECODE_COMPOSITE "{\"uri\":{\"address\":\"1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E\",\"amount\":10000120000,\"label\":\"&=\\\\n#\",\"message\":\"hello bitcoin\",\"r\":\"http://example.com?purchase=shoes&user=bob\",\"scheme\":\"bitcoin\"}}\n"

BOOST_AUTO_TEST_CASE(uri_decode__invoke__bip21_address__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_BIP21_ADDRESS);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__bip21_address_label__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?label=Luke-Jr" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_BIP21_ADDRESS_LABEL);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__bip21_address_amount_label__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?amount=20.3&label=Luke-Jr" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_BIP21_ADDRESS_AMOUNT_LABEL);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__bip21_address_amount_label_message__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?amount=50&label=Luke-Jr&message=Donation%20for%20project%20xyz" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_BIP21_ADDRESS_AMOUNT_LABEL_MESSAGE);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__bip21_address_extra_valid__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?somethingyoudontunderstand=50&somethingelseyoudontget=999" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_BIP21_ADDRESS);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__lower_case_scheme_empty__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_EMPTY);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__upper_case_scheme_empty__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "BITCOIN:" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_EMPTY);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__address__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_ADDRESS);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__amount__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?amount=100.0012" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_AMOUNT);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__label__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?label=%26%3D%5Cn%23" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_LABEL);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__message__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?message=hello%20bitcoin" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_MESSAGE);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__payment_request__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bitcoin:?r=http%3A%2F%2Fexample.com%3Fpurchase%3Dshoes%26user%3Dbob" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_PAYMENT_REQUEST);
}

BOOST_AUTO_TEST_CASE(uri_decode__invoke__composite__okay_output)
{
    BX_DECLARE_COMMAND(uri_decode);
    command.set_uri_argument({ "bItCoIn:1HT7xU2Ngenf7D4yocz2SAcnNLW7rK8d4E?amount=100.0012&label=%26%3D%5Cn%23&message=hello%20bitcoin&r=http%3A%2F%2Fexample.com%3Fpurchase%3Dshoes%26user%3Dbob" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(URI_DECODE_COMPOSITE);
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
