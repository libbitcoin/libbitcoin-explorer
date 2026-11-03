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

#include <bitcoin/explorer.hpp>

namespace io = bc::network::io;
namespace http = bc::network::http;

http_server::http_server(http::status status, const std::string& body) NOEXCEPT
  : acceptor_(context_.get_executor(),
        bc::system::config::authority{ BX_TEST_HTTP_AUTHORITY }.to_endpoint()),
    status_(status), body_(body), thread_([this]() NOEXCEPT { serve(); })
{
}

http_server::~http_server() NOEXCEPT
{
    acceptor_.close();

    if (thread_.joinable())
        thread_.join();
}

std::string http_server::url() const NOEXCEPT
{
    return "http://" BX_TEST_HTTP_AUTHORITY;
}

// Accepts until the acceptor is closed, so a retried request is served.
void http_server::serve() NOEXCEPT
{
    for (;;)
    {
        io::socket peer{ context_.get_executor() };
        bc::network::code ec{};
        acceptor_.accept(peer, ec);
        if (ec)
            return;

        http::flat_buffer buffer{};
        http::message<true, http::string_body> request{};
        http::read(peer, buffer, request, ec);

        if (!ec)
        {
            http::message<false, http::string_body> response{ status_,
                request.version() };
            response.set(http::field::content_type, "application/json");
            response.body() = body_;
            response.prepare_payload();
            http::write(peer, response, ec);
        }

        peer.close();
    }
}
