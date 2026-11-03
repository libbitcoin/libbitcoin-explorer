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

BC_AUTO_TEST_SUITE(online)
BC_AUTO_TEST_SUITE(watch_tx__invoke)

BC_AUTO_TEST_CASE(watch_tx__invoke__observed__okay_output)
{
    BX_DECLARE_COMMAND(watch_tx);
    const http_server server{ http_server::websocket, { "", "\"0000000000000000000000000000000000000000000000000000000000000002\"", "\"0000000000000000000000000000000000000000000000000000000000000001\"" }, true };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_duration_option(10);
    command.set_hash_argument({ "0000000000000000000000000000000000000000000000000000000000000001" });
    BX_REQUIRE_OKAY(command.invoke(output, error));
    BX_REQUIRE_OUTPUT("{}\n");
}

BC_AUTO_TEST_CASE(watch_tx__invoke__not_observed__failure_error)
{
    BX_DECLARE_COMMAND(watch_tx);
    const http_server server{ http_server::websocket, { "\"0000000000000000000000000000000000000000000000000000000000000002\"" }, true };
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_argument({ server.url() });
    command.set_duration_option(1);
    command.set_hash_argument({ "0000000000000000000000000000000000000000000000000000000000000001" });
    BX_REQUIRE_FAILURE(command.invoke(output, error));
    BX_REQUIRE_ERROR(BX_WATCH_TX_TIMEOUT "\n");
}

BC_AUTO_TEST_SUITE_END()
BC_AUTO_TEST_SUITE_END()
