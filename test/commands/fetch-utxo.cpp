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

// Unspent outputs of 500, 3000 and 1200 satoshi.
#define FETCH_UTXO_UNSPENT "[{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":0},\"value\":500},{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":1},\"value\":3000},{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":2},\"value\":1200}]"

BC_AUTO_TEST_SUITE(offline)
BC_AUTO_TEST_SUITE(fetch_utxo__invoke)

BC_AUTO_TEST_CASE(fetch_utxo__invoke__unreachable__failure_error)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    command.set_server_url_setting({ "http://127.0.0.1:1" });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BC_REQUIRE(!error.str().empty());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()

BC_AUTO_TEST_SUITE(online)
BC_AUTO_TEST_SUITE(fetch_utxo__invoke)

BC_AUTO_TEST_CASE(fetch_utxo__invoke__greedy_two_outputs__okay_largest_first)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, FETCH_UTXO_UNSPENT };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_satoshi_argument(4000);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("[{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":1},\"value\":3000},{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":2},\"value\":1200}]\n");
}

BC_AUTO_TEST_CASE(fetch_utxo__invoke__greedy_one_output__okay_largest)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, FETCH_UTXO_UNSPENT };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_satoshi_argument(3000);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("[{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":1},\"value\":3000}]\n");
}

BC_AUTO_TEST_CASE(fetch_utxo__invoke__individual__okay_smallest_sufficient)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, FETCH_UTXO_UNSPENT };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_algorithm_option({ "individual" });
    command.set_satoshi_argument(1000);
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("[{\"point\":{\"hash\":\"0000000000000000000000000000000000000000000000000000000000000000\",\"index\":2},\"value\":1200}]\n");
}

BC_AUTO_TEST_CASE(fetch_utxo__invoke__individual_insufficient__failure_error)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, FETCH_UTXO_UNSPENT };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_algorithm_option({ "individual" });
    command.set_satoshi_argument(3001);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_FETCH_UTXO_INSUFFICIENT "\n");
}

BC_AUTO_TEST_CASE(fetch_utxo__invoke__greedy_insufficient__failure_error)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, FETCH_UTXO_UNSPENT };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_satoshi_argument(4701);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_FETCH_UTXO_INSUFFICIENT "\n");
}

BC_AUTO_TEST_CASE(fetch_utxo__invoke__served_object__failure_error)
{
    BX_DECLARE_COMMAND(fetch_utxo);
    const http_server server{ network::http::status::ok, "{}" };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_hash_argument({ BX_GENESIS_BLOCK_HASH });
    command.set_satoshi_argument(1);
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BC_REQUIRE(!error.str().empty());
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
