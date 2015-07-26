/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
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
BOOST_AUTO_TEST_SUITE(uri_encode__invoke)

// BIP-21 vectors

BOOST_AUTO_TEST_CASE(uri_encode__invoke__address__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_bitcoin_address_argument({ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__address_label__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_bitcoin_address_argument({ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    command.set_label_option("Luke-Jr");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?label=Luke-Jr\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__address_label_amount__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_bitcoin_address_argument({ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    command.set_label_option("Luke-Jr");
    command.set_amount_option({ "20.3" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?amount=20.3&label=Luke-Jr\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__address_label_amount_message__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_bitcoin_address_argument({ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    command.set_label_option("Luke-Jr");
    command.set_amount_option({ "50" });
    command.set_message_option("Donation for project xyz");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L?amount=50&label=Luke-Jr&message=Donation%20for%20project%20xyz\n");
}

// additional (similar to libbitcoin vectors)

BOOST_AUTO_TEST_CASE(uri_encode__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__stealth_address__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_stealth_option({ "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__bitcoin_and_stealth_address__failure_error)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_bitcoin_address_argument({ "1NS17iag9jJgTHD1VXjvLCEnZuQ3rJED9L" });
    command.set_stealth_option({ "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_URI_ENCODE_ADDRESS_CONFLICT "\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__escaped_label__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_label_option("&=\\n#");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:?label=%26%3D%5Cn%23\n");
}

BOOST_AUTO_TEST_CASE(uri_encode__invoke__composite__okay_output)
{
    BX_DECLARE_COMMAND(uri_encode);
    command.set_stealth_option({ "hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i" });
    command.set_amount_option({ "100.0012" });
    command.set_label_option("&=\\n#");
    command.set_message_option("hello bitcoin");
    command.set_request_option({ "http://example.com?purchase=shoes&user=bob" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("bitcoin:hfFGUXFPKkQ5M6LC6aEUKMsURdhw93bUdYdacEtBA8XttLv7evZkira2i?amount=100.0012&label=%26%3D%5Cn%23&message=hello%20bitcoin&r=http://example.com?purchase%3Dshoes%26user%3Dbob\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
