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

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(watch_address__invoke)

// This will hang indefinately unless we fake the network calls, 
// so it's disabled here.
//BOOST_AUTO_TEST_CASE(watch_address__invoke__fist_address_info__okay)
//{
//    BX_DECLARE_NETWORK_COMMAND(watch_address);
//    command.set_format_option({ "info" });
//    command.set_bitcoin_address_argument({ BX_FIRST_ADDRESS });
//    BX_REQUIRE_OKAY(command.invoke(output, error));
//}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()