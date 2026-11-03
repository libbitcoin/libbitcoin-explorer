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

#include <string>
#include <vector>
#include <bitcoin/explorer.hpp>

namespace io = bc::network::io;
namespace http = bc::network::http;
using code = bc::network::code;
using authority = bc::system::config::authority;

static io::endpoint test_endpoint() NOEXCEPT
{
    return authority{ BX_TEST_HTTP_AUTHORITY }.to_endpoint();
}

http_server::http_server(http::status status,
    const std::string& body) NOEXCEPT
  : status_(status), body_(body), parts_{},
    acceptor_(pool_.service().get_executor(), test_endpoint()),
    peer_(pool_.service().get_executor())
{
    accept();
}

http_server::http_server(const std::vector<std::string>& parts) NOEXCEPT
  : status_(http::status::ok), body_{}, parts_(parts),
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
    {
        auto buffer = io::buffer(part);

        while (!ec && bc::is_nonzero(buffer.size()))
            buffer += peer_.write_some(buffer, ec);
    }
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

    if (!result)
        respond(result, request.version());

    peer_.close();
    accept();
}
