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
BOOST_AUTO_TEST_SUITE(seed__invoke)

#define BX_SEED_BITS_TO_TERMINATED_BASE16(bits) (2 * (bits / 8) + 1)

BOOST_AUTO_TEST_CASE(seed__invoke__minimum_size__okay_output)
{
    BX_DECLARE_COMMAND(seed);

    // Here we must explicitly set the default value, since we are bypassing
    // the boost parser and variable bindings which implement defaults.
    command.set_bit_length_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_SEED_BITS_TO_TERMINATED_BASE16(128));
}

BOOST_AUTO_TEST_CASE(seed__invoke__good_size__okay_output)
{
    BX_DECLARE_COMMAND(seed);
    command.set_bit_length_option(256);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_SEED_BITS_TO_TERMINATED_BASE16(256));
}

BOOST_AUTO_TEST_CASE(seed__invoke_big_size_okay_output)
{
    BX_DECLARE_COMMAND(seed);
    command.set_bit_length_option(512);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_SEED_BITS_TO_TERMINATED_BASE16(512));
}

BOOST_AUTO_TEST_CASE(seed__invoke__too_short__failure_error)
{
    BX_DECLARE_COMMAND(seed);
    command.set_bit_length_option(64);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SEED_BIT_LENGTH_UNSUPPORTED "\n");
}

BOOST_AUTO_TEST_CASE(seed__invoke__not_byte_aligned__failure_error)
{
    BX_DECLARE_COMMAND(seed);
    command.set_bit_length_option(129);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_SEED_BIT_LENGTH_UNSUPPORTED "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()