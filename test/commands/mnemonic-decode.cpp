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
BOOST_AUTO_TEST_SUITE(mnemonic_decode__invoke)

BOOST_AUTO_TEST_CASE(mnemonic_decode__invoke__12_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument(
    {
        { "eternity" },
        { "blood" },
        { "task" },
        { "eternity" },
        { "blood" },
        { "task" },
        { "eternity" },
        { "blood" },
        { "task" },
        { "eternity" },
        { "blood" },
        { "task" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("baadf00dbaadf00dbaadf00dbaadf00d\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_decode__invoke__2_words__okay_output)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument(
    {
        { "eternity" },
        { "blood" },
        { "task" }
    });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("baadf00d\n");
}

BOOST_AUTO_TEST_CASE(mnemonic_decode__invoke__3_words__failure_error)
{
    BX_DECLARE_COMMAND(mnemonic_decode);
    command.set_words_argument(
    {
        { "eternity" },
        { "blood" }
    });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_EC_MNEMONIC_DECODE_SHORT_SENTENCE "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()