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
#ifndef BX_TEST_FIXTURE_HTTP_SERVER_HPP
#define BX_TEST_FIXTURE_HTTP_SERVER_HPP

#include <string>
#include <vector>
#include <bitcoin/explorer.hpp>

#define BX_TEST_HTTP_AUTHORITY "127.0.0.1:65001"

// The acceptor runs on the fixture pool and answers each request with one
// canned response, re-arming so that a retry is served. The client under
// test drives its own context on the test thread, so the pool is stopped
// and joined before teardown and no completion outlives the case.
struct websocket_t {};

class http_server
{
public:
    DELETE_COPY_MOVE(http_server);
    static constexpr websocket_t websocket{};

    /// A well-formed response of the given status and body.
    http_server(bc::network::http::status status,
        const std::string& body) NOEXCEPT;

    /// The given bytes, one write per part, with no added headers.
    explicit http_server(const std::vector<std::string>& parts) NOEXCEPT;

    /// Accept an upgrade, send each message as a text frame and, if closing,
    /// a close frame. Other requests get an empty json response.
    http_server(websocket_t, const std::vector<std::string>& messages,
        bool close) NOEXCEPT;

    ~http_server() NOEXCEPT;

    /// The url of this server.
    std::string url() const NOEXCEPT;

private:
    void accept() NOEXCEPT;
    void handle_accept(const bc::network::code& ec) NOEXCEPT;
    void respond(bc::network::code& ec, unsigned version) NOEXCEPT;
    void respond_websocket(bc::network::code& ec,
        const bc::network::http::request_header& request) NOEXCEPT;

    const bc::network::http::status status_;
    const std::string body_;
    const std::vector<std::string> parts_;
    const std::vector<std::string> messages_;
    const bool websocket_;
    const bool close_;
    bc::network::threadpool pool_{ 1 };
    bc::network::io::acceptor acceptor_;
    bc::network::io::socket peer_;
};

#endif
