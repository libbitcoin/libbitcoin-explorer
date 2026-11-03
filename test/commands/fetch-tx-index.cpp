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
#include "../fixture/http_server.hpp"

BX_USING_NAMESPACES()

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(fetch_tx_index__invoke)

BC_AUTO_TEST_CASE(fetch_tx_index__invoke__unreachable__failure_error)
{
    BX_DECLARE_COMMAND(fetch_tx_index);
    command.set_server_url_setting({ "http://127.0.0.1:1" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BC_REQUIRE(!error.str().empty());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()

BC_AUTO_TEST_SUITE(online)
BC_AUTO_TEST_SUITE(fetch_tx_index__invoke)

BC_AUTO_TEST_CASE(fetch_tx_index__invoke__served_confirmed__okay_output)
{
    const http_server server{ network::http::status::ok, "{\"confirmed\":42}" };
    BX_DECLARE_COMMAND(fetch_tx_index);
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("42\n");
}

BC_AUTO_TEST_CASE(fetch_tx_index__invoke__served_unconfirmed__failure_error)
{
    const http_server server{ network::http::status::ok, "{}" };
    BX_DECLARE_COMMAND(fetch_tx_index);
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_FETCH_TX_INDEX_UNCONFIRMED "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
