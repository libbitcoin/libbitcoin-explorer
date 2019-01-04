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

#include "command.hpp"

BX_USING_NAMESPACES()

BOOST_AUTO_TEST_SUITE(network)
BOOST_AUTO_TEST_SUITE(subscribe_block__invoke)

BOOST_AUTO_TEST_CASE(subscribe_block__invoke__one_second_duration__okay)
{
    BX_DECLARE_CLIENT_COMMAND(subscribe_block);
    command.set_duration_option(1);
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_CASE(subscribe_block__invoke__testnet_one_second_duration__okay)
{
    BX_DECLARE_CLIENT_TESTNET_COMMAND(subscribe_block);
    command.set_duration_option(1);
    command.set_server_url_argument({ BX_TESTNET_TRANSACTION });
    BX_REQUIRE_OKAY(command.invoke(output, error));
}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
