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

BOOST_AUTO_TEST_SUITE(embed_address__invoke)

// $ cat my_sculpture.jpg | sx address-embed
// 1N9v8AKBqst9MNceV3gLmFKsgkKv1bZcBU
// Now send some Bitcoin to that address and it will be embedded
// in the blockchain as a record of the data passed in.

BOOST_AUTO_TEST_CASE(address_embed__invoke__always__failure_error)
{
    // sx address-embed
    SX_DECLARE_COMMAND(address_embed);
    SX_REQUIRE_FAILURE(command.invoke(output, error));
    SX_REQUIRE_ERROR(SX_ADDRESS_EMBED_NOT_IMPLEMENTED "\n");
}

BOOST_AUTO_TEST_SUITE_END()