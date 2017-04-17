/**
 * Copyright (c) 2011-2017 libbitcoin developers (see AUTHORS)
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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(watch_stealth__invoke)

BOOST_AUTO_TEST_CASE(watch_stealth__invoke__short_address__failure)
{
    BX_DECLARE_CLIENT_COMMAND(watch_stealth);
    command.set_duration_option(1);
    command.set_prefix_argument({ "1010101" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_WATCH_STEALTH_PREFIX_TOO_SHORT "\n");
}

BOOST_AUTO_TEST_CASE(watch_stealth__invoke__long_address__failure)
{
    BX_DECLARE_CLIENT_COMMAND(watch_stealth);
    command.set_duration_option(1);
    command.set_prefix_argument({ "101010101010101010101010101010101" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_WATCH_STEALTH_PREFIX_TOO_LONG "\n");
}

BOOST_AUTO_TEST_CASE(watch_stealth__invoke__one_second_duration__okay)
{
    BX_DECLARE_CLIENT_COMMAND(watch_stealth);
    command.set_duration_option(1);
    command.set_prefix_argument({ "10101010" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
