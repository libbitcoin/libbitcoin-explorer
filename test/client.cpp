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
#include <bitcoin/explorer.hpp>
#include "fixture/http_server.hpp"

using namespace bc;
using namespace bc::explorer;
using namespace bc::system;

// A response body that the client must read to the end of the stream.
#define CLIENT_EOF_RESPONSE "HTTP/1.1 200 OK\r\nConnection: close\r\n\r\n42"
#define CLIENT_SPLIT_HEAD "HTTP/1.1 200 OK\r\nContent-Length: 2\r\n\r\n"

BC_AUTO_TEST_SUITE(client_tests)

BC_AUTO_TEST_CASE(client__get__served_value__true_expected)
{
    const http_server server{ network::http::status::ok, "42" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "top"));
    BC_REQUIRE(error.empty());
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__get__served_query__true_expected)
{
    const http_server server{ network::http::status::ok, "42" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "tx/42", "witness=false"));
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__get__served_not_found__false_error)
{
    const http_server server{ network::http::status::not_found, "" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(!instance.get(out, error, "top"));
    BC_REQUIRE(!error.empty());
}

BC_AUTO_TEST_CASE(client__get__served_invalid_json__false_error)
{
    const http_server server{ network::http::status::ok, "baadf00d" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(!instance.get(out, error, "top"));
    BC_REQUIRE(!error.empty());
}

BC_AUTO_TEST_CASE(client__get__unreachable__false_error)
{
    client instance{ { "http://127.0.0.1:65002" }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(!instance.get(out, error, "top"));
    BC_REQUIRE(!error.empty());
}

BC_AUTO_TEST_CASE(client__get__split_response__true_expected)
{
    const http_server server{ { CLIENT_SPLIT_HEAD, "42" } };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "top"));
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__get__eof_delimited_response__true_expected)
{
    const http_server server{ { CLIENT_EOF_RESPONSE } };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "top"));
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__construct__command_argument_with_port__argument_server)
{
    const http_server server{ network::http::status::ok, "42" };
    commands::fetch_height command;
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_setting({ "http://127.0.0.1:65002" });
    client instance{ command, { server.url() } };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "top"));
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__construct__command_argument_without_port__setting_server)
{
    const http_server server{ network::http::status::ok, "42" };
    commands::fetch_height command;
    command.set_server_connect_timeout_seconds_setting(10);
    command.set_server_url_setting({ server.url() });
    client instance{ command, {} };
    json::value out{};
    std::string error{};
    BC_REQUIRE(instance.get(out, error, "top"));
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__fetch__served_value__true_no_error)
{
    const http_server server{ network::http::status::ok, "42" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::stringstream error{};
    BC_REQUIRE(instance.fetch(out, error, "top"));
    BC_REQUIRE(error.str().empty());
    BC_REQUIRE_EQUAL(json::value_to<uint32_t>(out), 42u);
}

BC_AUTO_TEST_CASE(client__fetch__served_not_found__false_error)
{
    const http_server server{ network::http::status::not_found, "" };
    client instance{ { server.url() }, 0, 10 };
    json::value out{};
    std::stringstream error{};
    BC_REQUIRE(!instance.fetch(out, error, "top"));
    BC_REQUIRE_EQUAL(error.str(), "Server query failed: 404 Not Found.\n");
}

BC_AUTO_TEST_CASE(client__block_path__null_hash__height_path)
{
    BC_REQUIRE_EQUAL(block_path(null_hash, 42), "block/height/42");
}

BC_AUTO_TEST_CASE(client__block_path__hash__hash_path)
{
    BC_REQUIRE_EQUAL(block_path(one_hash, 42), "block/hash/" + encode_hash(one_hash));
}

BC_AUTO_TEST_SUITE_END()
