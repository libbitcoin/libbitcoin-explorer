/*
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(addr_validate__invoke)

BOOST_AUTO_TEST_CASE(addr_validate__invoke__one_address__okay_output)
{
    // $ sx addr-validate 3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy
    SX_DECLARE_COMMAND(addr_validate);
    command.set_addresss_argument({{ "3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy" }});
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("");
}

BOOST_AUTO_TEST_CASE(addr_validate__invoke__two_addresses__okay_output)
{
    // $ sx addr-validate 3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz
    SX_DECLARE_COMMAND(addr_validate);
    command.set_addresss_argument(
    { 
        { "3J98t1WpEZ73CNmQviecrnyiWrnqRhWNLy" },
        { "134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz" }
    });
    SX_REQUIRE_OKAY(command.invoke(output, error));
    SX_REQUIRE_OUTPUT("");
}

BOOST_AUTO_TEST_SUITE_END()