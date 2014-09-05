/*
 * Copyright (c)2011-2014 libbitcoin developers (see AUTHORS)
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
#include "precompile.hpp"
#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(help__invoke)

BOOST_AUTO_TEST_CASE(help__invoke__bogus_command__failure)
{
    BX_DECLARE_COMMAND(help);
    command.set_command_argument("booger");
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    //BX_REQUIRE_ERROR("TODO");
}

BOOST_AUTO_TEST_CASE(help__invoke__no_command__okay_output)
{
    BX_DECLARE_COMMAND(help);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    //BX_REQUIRE_OUTPUT("TODO");
}
BOOST_AUTO_TEST_CASE(help__invoke__valid_command__okay_output)
{
    BX_DECLARE_COMMAND(help);
    command.set_command_argument("help");
    BX_REQUIRE_OKAY(command.invoke(output, error));
    //BX_REQUIRE_OUTPUT("TODO");
}

BOOST_AUTO_TEST_SUITE_END()
