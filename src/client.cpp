#include <bitcoin/explorer/client.hpp>

#include <chrono>
#include <memory>
#include <string>
#include <bitcoin/network.hpp>
#include <bitcoin/system.hpp>

namespace libbitcoin {
namespace explorer {

namespace io = network::io;
namespace http = network::http;

constexpr auto user_agent = "libbitcoin-explorer";
constexpr auto version_prefix = "/v1/";
constexpr auto json_format = "?format=json";

client::client(const system::config::url& url, uint8_t retries,
    uint16_t timeout_seconds) NOEXCEPT
  : url_(url.to_local()), retries_(retries),
    timeout_seconds_(timeout_seconds)
{
}

BC_PUSH_WARNING(NO_THROW_IN_NOEXCEPT)

// One http GET, each step of which (resolve, connect, write, read) is bounded
// by the timeout. The context runs on the calling thread.
class fetcher
  : public std::enable_shared_from_this<fetcher>
{
public:
    fetcher(io::context& service, const std::string& host, uint16_t port,
        const std::string& target, std::chrono::seconds timeout) NOEXCEPT
      : resolver_(service), socket_(service), timer_(service), host_(host),
        port_(port), timeout_(timeout)
    {
        http::message<true, http::empty_body> request{ http::verb::get,
            target, http::version_1_1 };

        request.set(http::field::host, host);
        request.set(http::field::user_agent, user_agent);
        request.set(http::field::connection, "close");

        http::serializer<true, http::empty_body> serializer{ request };
        while (!serializer.is_done() && !ec_)
            for (const auto& buffer: serializer.next(ec_))
                request_.append(system::pointer_cast<const char>(
                    buffer.data()), buffer.size());
    }

    void start() NOEXCEPT
    {
        if (ec_)
            return;

        arm();
        resolver_.async_resolve(host_, std::to_string(port_),
            [self = shared_from_this()](const network::code& ec,
                const io::endpoints& range) NOEXCEPT
            {
                self->handle_resolve(ec, range);
            });
    }

    const network::code& result() const NOEXCEPT
    {
        return ec_;
    }

    http::message<false, http::string_body>& response() NOEXCEPT
    {
        return parser_.get();
    }

private:
    // Expiry cancels the pending step (the timer handler is canceled by the
    // next arm or by completion).
    void arm() NOEXCEPT
    {
        timer_.expires_after(timeout_);
        timer_.async_wait([self = shared_from_this()](const network::code& ec) NOEXCEPT
        {
            if (ec)
                return;

            self->timed_out_ = true;
            self->resolver_.cancel();
            self->socket_.close();
        });
    }

    bool fail(const network::code& ec) NOEXCEPT
    {
        if (!ec)
            return false;

        ec_ = timed_out_ ? network::code{ network::error::channel_timeout } : ec;
        timer_.cancel();
        socket_.close();
        return true;
    }

    void handle_resolve(const network::code& ec, const io::endpoints& range) NOEXCEPT
    {
        if (fail(ec))
            return;

        arm();
        io::async_connect(socket_, range,
            [self = shared_from_this()](const network::code& ec,
                const io::endpoint&) NOEXCEPT
            {
                self->handle_connect(ec);
            });
    }

    void handle_connect(const network::code& ec) NOEXCEPT
    {
        if (fail(ec))
            return;

        arm();
        io::async_write(socket_, io::buffer(std::as_const(request_)),
            [self = shared_from_this()](const network::code& ec, size_t) NOEXCEPT
            {
                self->handle_write(ec);
            });
    }

    void handle_write(const network::code& ec) NOEXCEPT
    {
        if (fail(ec))
            return;

        read();
    }

    void read() NOEXCEPT
    {
        arm();
        socket_.async_read_some(buffer_.prepare(http::transfer_size),
            [self = shared_from_this()](const network::code& ec, size_t size) NOEXCEPT
            {
                self->handle_read(ec, size);
            });
    }

    void handle_read(const network::code& ec, size_t size) NOEXCEPT
    {
        buffer_.commit(size);
        network::code parse{};
        while (is_nonzero(buffer_.size()) && !parser_.is_done())
        {
            const auto used = parser_.put(buffer_.data(), parse);
            buffer_.consume(used);
            if (parse == network::error::http_error_t::need_more)
            {
                parse.clear();
                break;
            }

            if (parse || is_zero(used))
                break;
        }

        // The connection closes after the response (connection: close).
        if (!parse && !parser_.is_done() && ec == network::error::peer_disconnect)
            parser_.put_eof(parse);

        if (parser_.is_done())
        {
            ec_ = network::error::success;
            timer_.cancel();
            socket_.close();
            return;
        }

        if (fail(parse ? parse : ec))
            return;

        read();
    }

    io::resolver resolver_;
    io::socket socket_;
    io::steady_timer timer_;
    const std::string host_;
    const uint16_t port_;
    const std::chrono::seconds timeout_;
    std::string request_{};
    http::flat_buffer buffer_{};
    http::parser<false, http::string_body> parser_{};
    network::code ec_{};
    bool timed_out_{};
};

// Returns false and populates error on any failure.
static bool fetch(std::string& out, std::string& error,
    const system::config::url& url, uint16_t timeout_seconds,
    const std::string& target) NOEXCEPT
{
    io::context service{};
    const auto instance = std::make_shared<fetcher>(service, url.host(),
        url.port(), target, std::chrono::seconds(timeout_seconds));

    instance->start();
    service.run();

    if (const auto& ec = instance->result())
    {
        error = ec.message();
        return false;
    }

    const auto& response = instance->response();
    if (response.result() != http::status::ok)
    {
        error = std::to_string(response.result_int()) + " " +
            std::string(response.reason());
        return false;
    }

    out = response.body();
    return true;
}

BC_POP_WARNING()

bool client::get(system::json::value& out, std::string& error,
    const std::string& path, const std::string& query) NOEXCEPT
{
    const auto target = version_prefix + path + json_format +
        (query.empty() ? "" : "&" + query);

    std::string body{};
    for (uint8_t attempt{}; attempt <= retries_; ++attempt)
        if (fetch(body, error, url_, timeout_seconds_, target))
            break;
        else if (attempt == retries_)
            return false;

    system::code ec{};
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
