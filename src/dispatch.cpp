/**
 * Copyright (c) 2011-2015 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin-explorer.
 *
 * libbitcoin-explorer is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License with
 * additional permissions to the one published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version. For more information see LICENSE.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <bitcoin/explorer/dispatch.hpp>

#include <iostream>
#include <string>
#include <boost/core/null_deleter.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/program_options.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/smart_ptr/make_shared.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/commands/send-tx-node.hpp>
#include <bitcoin/explorer/commands/send-tx-p2p.hpp>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/display.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/parser.hpp>
#include <bitcoin/bitcoin.hpp>

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace boost::system;

namespace logging = boost::log;
namespace expr = boost::log::expressions;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;

namespace libbitcoin {
namespace explorer {

typedef sinks::synchronous_sink<sinks::text_ostream_backend> text_sink;

template<typename Stream>
static void add_text_sink(boost::shared_ptr<Stream>& stream)
{
    // Construct the sink
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    // Add a stream to write log to
    sink->locked_backend()->add_stream(stream);

    sink->set_formatter(expr::stream << "["
        << expr::format_date_time<boost::posix_time::ptime, char>(
            log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
        << "][" << log::attributes::channel
        << "][" << log::attributes::severity
        << "]: " << expr::smessage);

    // Register the sink in the logging core
    logging::core::get()->add_sink(sink);
}

template<typename Stream, typename FunT>
static void add_text_sink(boost::shared_ptr<Stream>& stream,
    FunT const& filter)
{
    // Construct the sink
    boost::shared_ptr<text_sink> sink = boost::make_shared<text_sink>();

    // Add a stream to write log to
    sink->locked_backend()->add_stream(stream);

    sink->set_filter(filter);

    sink->set_formatter(expr::stream << "["
        << expr::format_date_time<boost::posix_time::ptime, char>(
            log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
        << "][" << log::attributes::channel
        << "][" << log::attributes::severity
        << "]: " << expr::smessage);

    // Register the sink in the logging core
    logging::core::get()->add_sink(sink);
}

static void initialize_logging(boost::shared_ptr<bc::ofstream>& debug,
    boost::shared_ptr<bc::ofstream>& error,
    boost::shared_ptr<std::ostream>& output_stream,
    boost::shared_ptr<std::ostream>& error_stream)
{
    auto error_filter = (log::attributes::severity == log::severity::warning)
        || (log::attributes::severity == log::severity::error)
        || (log::attributes::severity == log::severity::fatal);

    auto info_filter = (log::attributes::severity == log::severity::info);

    add_text_sink(debug);
    add_text_sink(error, error_filter);
    add_text_sink(output_stream, info_filter);
    add_text_sink(output_stream, error_filter);
}

// Swap Unicode input stream for binary stream in Windows builds.
static std::istream& get_command_input(command& command, std::istream& input)
{
#ifdef _MSC_VER
    if (command.requires_raw_input())
    {
        bc::set_binary_stdin();
        return std::cin;
    }

    bc::set_utf8_stdin();
#endif

    return input;
}

// Swap Unicode output stream for binary stream in Windows builds.
static std::ostream& get_command_output(command& command, std::ostream& output)
{
#ifdef _MSC_VER
    if (command.requires_raw_output())
    {
        bc::set_binary_stdout();
        return std::cout;
    }

    bc::set_utf8_stdout();
#endif

    return output;
}

// Set Unicode error stream in Windows builds.
static std::ostream& get_command_error(command& command, std::ostream& error)
{
    bc::set_utf8_stderr();
    return error;
}

console_result dispatch(int argc, const char* argv[], 
    std::istream& input, std::ostream& output, std::ostream& error)
{
    if (argc == 1)
    {
        display_usage(output);
        return console_result::okay;
    }

    return dispatch_command(argc - 1, &argv[1], input, output, error);
}

console_result dispatch_command(int argc, const char* argv[],
    std::istream& input, std::ostream& output, std::ostream& error)
{
    const std::string target(argv[0]);
    const auto command = find(target);

    if (!command)
    {
        const std::string superseding(formerly(target));
        display_invalid_command(error, target, superseding);
        return console_result::failure;
    }

    auto& in = get_command_input(*command, input);
    auto& err = get_command_error(*command, error);
    auto& out = get_command_output(*command, output);

    parser metadata(*command);
    std::string error_message;

    if (!metadata.parse(error_message, in, argc, argv))
    {
        display_invalid_parameter(error, error_message);
        return console_result::failure;
    }

    if (metadata.help())
    {
        command->write_help(output);
        return console_result::okay;
    }

    // TODO: move log sink logic to console app.
    if ((target == commands::send_tx_node::symbol()) ||
        (target == commands::send_tx_p2p::symbol()))
    {
        boost::shared_ptr<std::ostream> console_out(&output, boost::null_deleter());
        boost::shared_ptr<std::ostream> console_err(&error, boost::null_deleter());
        boost::shared_ptr<bc::ofstream> debug_log = boost::make_shared<bc::ofstream>(
            command->get_network_debug_file_setting().string(),
            std::ofstream::out | std::ofstream::app);
        boost::shared_ptr<bc::ofstream> error_log = boost::make_shared<bc::ofstream>(
            command->get_network_error_file_setting().string(),
            std::ofstream::out | std::ofstream::app);

        initialize_logging(debug_log, error_log, console_out, console_err);
    }

    return command->invoke(out, err);
}

} // namespace explorer
} // namespace libbitcoin
