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
BOOST_AUTO_TEST_SUITE(entropy__invoke)

#define BX_ENTROPY_BITS_TO_TERMINATED_BASE16(bits) (2 * (bits / 8) + 1)

BOOST_AUTO_TEST_CASE(entropy__invoke__minimum_size__okay_output)
{
    BX_DECLARE_COMMAND(entropy);

    // Here we must explicitly set the default value, since we are bypassing
    // the boost parser and variable bindings which implement defaults.
    command.set_bits_option(128);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_ENTROPY_BITS_TO_TERMINATED_BASE16(128));
}

BOOST_AUTO_TEST_CASE(entropy__invoke__good_size__okay_output)
{
    BX_DECLARE_COMMAND(entropy);
    command.set_bits_option(256);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_ENTROPY_BITS_TO_TERMINATED_BASE16(256));
}

BOOST_AUTO_TEST_CASE(entropy__invoke_big_size_okay_output)
{
    BX_DECLARE_COMMAND(entropy);
    command.set_bits_option(512);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BOOST_REQUIRE(output.str().size() == BX_ENTROPY_BITS_TO_TERMINATED_BASE16(512));
}

BOOST_AUTO_TEST_CASE(entropy__invoke__too_short__failure_error)
{
    BX_DECLARE_COMMAND(entropy);
    command.set_bits_option(64);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ENTROPY_SHORT_BIT_LENGTH "\n");
}

BOOST_AUTO_TEST_CASE(entropy__invoke__not_byte_aligned__failure_error)
{
    BX_DECLARE_COMMAND(entropy);
    command.set_bits_option(129);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_ENTROPY_SHORT_BIT_LENGTH "\n");
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
