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

BOOST_AUTO_TEST_SUITE(offline)
BOOST_AUTO_TEST_SUITE(sha256__invoke)

// vectors
#define BX_SHA256_NIST_MESSAGE_A "abc"
#define BX_SHA256_NIST_MESSAGE_B "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"

#define BX_SHA256_NIST_DIGEST_A "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
#define BX_SHA256_NIST_DIGEST_B "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"

BOOST_AUTO_TEST_CASE(sha256__invoke__NIST_SHA256_A__okay_output)
{
    BX_DECLARE_COMMAND(sha256);
    command.set_base16_argument(base16(raw(BX_SHA256_NIST_MESSAGE_A)));
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SHA256_NIST_DIGEST_A "\n");
}

BOOST_AUTO_TEST_CASE(sha256__invoke__NIST_SHA256_B__okay_output)
{
    BX_DECLARE_COMMAND(sha256);
    command.set_base16_argument(base16(raw(BX_SHA256_NIST_MESSAGE_B)));
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT(BX_SHA256_NIST_DIGEST_B "\n");
}

BOOST_AUTO_TEST_CASE(sha256__invoke__good_food__okay_output)
{
    BX_DECLARE_COMMAND(sha256);
    command.set_base16_argument({ "900df00d" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("f0ebe3bd55115e573ba35c2b1b65a923ff64c7a548d0deab73f9314754a9149d\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()