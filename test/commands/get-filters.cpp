/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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

// Sponsored in part by Digital Contract Design, LLC

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(get_filters__invoke)

#define BLOCK_49291_HASH "0000000018b07dca1b28b4b5a119f6d6e71698ce1ed96f143f54179ce177a19c"

BOOST_AUTO_TEST_CASE(get_filters__invoke__mainnet__success)
{
    BX_DECLARE_PEER_COMMAND(get_filters);

    // Send p2p log output to /dev/null.
    log::initialize();

    command.set_host_option(BX_MAINNET_HOST);
    command.set_port_option(BX_MAINNET_PORT);
    command.set_hash_argument({ BLOCK_49291_HASH });
    command.set_height_argument(49285);
//    command.set_filter_type_argument(0);

    // Currently expecting failure due to service bit absence
    BX_REQUIRE_FAILURE(command.invoke(output, error));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
