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
BOOST_AUTO_TEST_SUITE(base58_encode__invoke)

// vectors
// tools.ietf.org/html/rfc4648#section-10

#define BX_BASE64_ENCODE_EMPTY_DECODED ""
#define BX_BASE64_ENCODE_RFC4648_DECODED_A "foo"
#define BX_BASE64_ENCODE_RFC4648_DECODED_B "foob"
#define BX_BASE64_ENCODE_RFC4648_DECODED_C "fooba"
#define BX_BASE64_ENCODE_RFC4648_DECODED_D "foobar"

#define BX_BASE64_ENCODE_EMPTY_ENCODED ""
#define BX_BASE64_ENCODE_RFC4648_ENCODED_A "Zm9v"
#define BX_BASE64_ENCODE_RFC4648_ENCODED_B "Zm9vYg=="
#define BX_BASE64_ENCODE_RFC4648_ENCODED_C "Zm9vYmE="
#define BX_BASE64_ENCODE_RFC4648_ENCODED_D "Zm9vYmFy"

BOOST_AUTO_TEST_CASE(base64_encode__invoke__empty__okay_output)
{
    BX_DECLARE_COMMAND(base64_encode);
    command.set_data_argument({ BX_BASE64_ENCODE_EMPTY_DECODED });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE64_ENCODE_EMPTY_ENCODED "\n");
}

BOOST_AUTO_TEST_CASE(base64_encode__invoke__RFC4648_A_okay_output)
{
    BX_DECLARE_COMMAND(base64_encode);
    command.set_data_argument({ BX_BASE64_ENCODE_RFC4648_DECODED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE64_ENCODE_RFC4648_ENCODED_A "\n");
}

BOOST_AUTO_TEST_CASE(base64_encode__invoke__RFC4648_B_okay_output)
{
    BX_DECLARE_COMMAND(base64_encode);
    command.set_data_argument({ BX_BASE64_ENCODE_RFC4648_DECODED_B });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE64_ENCODE_RFC4648_ENCODED_B "\n");
}

BOOST_AUTO_TEST_CASE(base64_encode__invoke__RFC4648_C_okay_output)
{
    BX_DECLARE_COMMAND(base64_encode);
    command.set_data_argument({ BX_BASE64_ENCODE_RFC4648_DECODED_C });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE64_ENCODE_RFC4648_ENCODED_C "\n");
}

BOOST_AUTO_TEST_CASE(base64_encode__invoke__RFC4648_D_okay_output)
{
    BX_DECLARE_COMMAND(base64_encode);
    command.set_data_argument({ BX_BASE64_ENCODE_RFC4648_DECODED_D });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE64_ENCODE_RFC4648_ENCODED_D "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()