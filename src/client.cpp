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
#include <bitcoin/explorer/client.hpp>

#include <chrono>
#include <string>
#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = boost::beast::http;
using tcp = boost::asio::ip::tcp;

constexpr auto user_agent = "libbitcoin-explorer";
constexpr auto version_prefix = "/v1/";
constexpr auto json_format = "?format=json";

client::client(const system::config::url& url, uint8_t retries,
    uint16_t timeout_seconds) NOEXCEPT
  : url_(url.to_local()), retries_(retries),
    timeout_seconds_(timeout_seconds)
{
}

// Returns false and populates error on any failure.
static bool fetch(std::string& out, std::string& error,
    const system::config::url& url, uint16_t timeout_seconds,
    const std::string& target) NOEXCEPT
{
    try
    {
        const auto timeout = std::chrono::seconds(timeout_seconds);
        asio::io_context service{};
        beast::tcp_stream stream(service);

        tcp::resolver resolver(service);
        const auto port = std::to_string(url.port());
        const auto endpoints = resolver.resolve(url.host(), port);

        stream.expires_after(timeout);
        stream.connect(endpoints);

        http::request<http::empty_body> request{ http::verb::get, target, 11 };
        request.set(http::field::host, url.host());
        request.set(http::field::user_agent, user_agent);
        request.set(http::field::connection, "close");

        stream.expires_after(timeout);
        http::write(stream, request);

        beast::flat_buffer buffer{};
        http::response<http::string_body> response{};

        stream.expires_after(timeout);
        http::read(stream, buffer, response);

        if (response.result() != http::status::ok)
        {
            error = std::to_string(response.result_int()) + " " +
                std::string(response.reason());
            return false;
        }

        out = response.body();

        beast::error_code ignored{};
        stream.socket().shutdown(tcp::socket::shutdown_both, ignored);
        return true;
    }
    catch (const std::exception& e)
    {
        error = e.what();
        return false;
    }
}

bool client::get(system::json::value& out, std::string& error,
    const std::string& path) NOEXCEPT
{
    const auto target = version_prefix + path + json_format;

    std::string body{};
    for (uint8_t attempt{}; attempt <= retries_; ++attempt)
        if (fetch(body, error, url_, timeout_seconds_, target))
            break;
        else if (attempt == retries_)
            return false;

    boost::system::error_code ec{};
    out = system::json::parse(body, ec);
    if (ec)
    {
        error = ec.message();
        return false;
    }

    return true;
}

} // namespace explorer
} // namespace libbitcoin
