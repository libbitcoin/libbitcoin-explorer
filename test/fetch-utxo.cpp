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

BOOST_AUTO_TEST_SUITE(fetch_utxo__invoke)

BOOST_AUTO_TEST_CASE(fetch_utxo__invoke__zero_satoshi__failure_error)
{
    // $ sx fetch-utxo 0 bogus
    SX_DECLARE_COMMAND(fetch_utxo);
    command.set_satoshi_argument(0);
    //command.set_addresss_argument({{ "bogus" }});
    SX_REQUIRE_FAILURE(command.invoke(input, output, error));
    SX_REQUIRE_ERROR(SX_FETCH_UTXO_NOT_IMPLEMENTED "\n");
}

BOOST_AUTO_TEST_SUITE_END()