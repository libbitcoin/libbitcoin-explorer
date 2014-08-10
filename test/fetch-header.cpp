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
#include "precompile.hpp"
#include "command.hpp"

SX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(fetch_header__invoke)

// DISABLED until client-server calls are isolated for test.

//BOOST_AUTO_TEST_CASE(fetch_header__invoke__hash__okay)
//{
//    // $ sx fetch-header --hash 69735d70ada1be32ff39b49c6fc2390b03e9d5eed8918ed10fe42c8cbabf62d4
//    SX_DECLARE_COMMAND(fetch_header);
//    SX_REQUIRE_OKAY(command.invoke(output, error));
//}

//BOOST_AUTO_TEST_CASE(fetch_header__invoke__height__okay)
//{
//    // $ sx fetch-header --height 42
//    SX_DECLARE_COMMAND(fetch_header);
//    SX_REQUIRE_OKAY(command.invoke(output, error));
//}

//BOOST_AUTO_TEST_CASE(fetch_header_hash__invoke__height_hash__failure)
//{
//    // $ sx fetch-header --height 42 --hash 69735d70ada1be32ff39b49c6fc2390b03e9d5eed8918ed10fe42c8cbabf62d4
//    SX_DECLARE_COMMAND(fetch_header);
//    SX_REQUIRE_FAILURE(command.invoke(output, error));
//}

BOOST_AUTO_TEST_SUITE_END()