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
// #include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(bas16_decode__invoke)

// vectors
#define BX_BASE16_DECODE_NIST_DECODED_A "abc"
#define BX_BASE16_DECODE_NIST_DECODED_B "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"

#define BX_BASE16_DECODE_NIST_ENCODED_A "616263"
#define BX_BASE16_DECODE_NIST_ENCODED_B "6162636462636465636465666465666765666768666768696768696a68696a6b696a6b6c6a6b6c6d6b6c6d6e6c6d6e6f6d6e6f706e6f7071"

BOOST_AUTO_TEST_CASE(base16_decode__invoke__NIST_SHA256_A__okay_output)
{
    BX_DECLARE_COMMAND(base16_decode);
    command.set_base16_argument({ BX_BASE16_DECODE_NIST_ENCODED_A });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE16_DECODE_NIST_DECODED_A "\n");
}

BOOST_AUTO_TEST_CASE(base16_decode__invoke__NIST_SHA256_B__okay_output)
{
    BX_DECLARE_COMMAND(base16_decode);
    command.set_base16_argument({ BX_BASE16_DECODE_NIST_ENCODED_B });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_BASE16_DECODE_NIST_DECODED_B "\n");
}

BOOST_AUTO_TEST_SUITE_END()