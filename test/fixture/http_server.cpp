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
#include "http_server.hpp"

#include <array>
#include <string>
#include <vector>
#include <bitcoin/explorer.hpp>

namespace io = bc::network::io;
namespace http = bc::network::http;
namespace ws = bc::network::ws;
using code = bc::network::code;
using authority = bc::system::config::authority;

static io::endpoint test_endpoint() NOEXCEPT
{
    return authority{ BX_TEST_HTTP_AUTHORITY }.to_endpoint();
}

http_server::http_server(http::status status,
    const std::string& body) NOEXCEPT
  : status_(status), body_(body), parts_{}, messages_{}, websocket_(false),
    close_(false),
    acceptor_(pool_.service().get_executor(), test_endpoint()),
    peer_(pool_.service().get_executor())
{
    accept();
}

http_server::http_server(const std::vector<std::string>& parts) NOEXCEPT
  : status_(http::status::ok), body_{}, parts_(parts), messages_{},
    websocket_(false), close_(false),
    acceptor_(pool_.service().get_executor(), test_endpoint()),
    peer_(pool_.service().get_executor())
{
    accept();
}

http_server::http_server(websocket_t, const std::vector<std::string>& messages,
    bool close) NOEXCEPT
  : status_(http::status::ok), body_("{}"), parts_{}, messages_(messages),
    websocket_(true), close_(close),
    acceptor_(pool_.service().get_executor(), test_endpoint()),
    peer_(pool_.service().get_executor())
{
    accept();
}

http_server::~http_server() NOEXCEPT
{
    acceptor_.close();
    peer_.close();
    pool_.stop();
    pool_.join();
}

std::string http_server::url() const NOEXCEPT
{
    return "http://" BX_TEST_HTTP_AUTHORITY;
}

void http_server::accept() NOEXCEPT
{
    acceptor_.async_accept(peer_, [this](const code& ec) NOEXCEPT
    {
        handle_accept(ec);
    });
}

static void write_all(io::socket& peer, const std::string& data,
    code& ec) NOEXCEPT
{
    auto buffer = io::buffer(data);

    while (!ec && bc::is_nonzero(buffer.size()))
        buffer += peer.write_some(buffer, ec);
}

// A server frame is unmasked, with a one byte length (messages are short).
static void write_frame(io::socket& peer, uint8_t opcode,
    const std::string& payload, code& ec) NOEXCEPT
{
    const auto length = static_cast<char>(payload.size());
    const std::string header{ static_cast<char>(opcode), length };
    write_all(peer, header + payload, ec);
}

// Raw parts are written one part per write, so a response that arrives in
// pieces (or without a content length) can be presented to the client.
void http_server::respond(code& ec, unsigned version) NOEXCEPT
{
    if (parts_.empty())
    {
        http::message<false, http::string_body> response{ status_, version };
        response.set(http::field::content_type, "application/json");
        response.body() = body_;
        response.prepare_payload();
        http::write(peer_, response, ec);
        return;
    }

    for (const auto& part: parts_)
        write_all(peer_, part, ec);
}

// After the messages the peer's frames are drained until it closes, or
// until its deadline closes the socket.
void http_server::respond_websocket(code& ec,
    const http::request_header& request) NOEXCEPT
{
    ws::response response{};
    ec = ws::accept(response, request);
    if (ec)
        return;

    http::write(peer_, response, ec);
    for (const auto& message: messages_)
        write_frame(peer_, 0x81, message, ec);

    if (close_)
        write_frame(peer_, 0x88, std::string{ '\x03', '\xe8' }, ec);

    std::array<uint8_t, 64> scratch{};
    while (!ec)
        peer_.read_some(io::buffer(scratch), ec);
}

// The request and response are synchronous on the single pool thread, so
// the exchange completes before the next accept is armed.
void http_server::handle_accept(const code& ec) NOEXCEPT
{
    if (ec)
        return;

    code result{};
    http::flat_buffer buffer{};
    http::message<true, http::string_body> request{};
    http::read(peer_, buffer, request, result);
    if (result == bc::network::error::upgrade)
        result.clear();

    if (!result)
    {
        if (websocket_ && request.count(http::field::upgrade) > 0u)
            respond_websocket(result, request.base());
        else
            respond(result, request.version());
    }

    peer_.close();
    accept();
}
