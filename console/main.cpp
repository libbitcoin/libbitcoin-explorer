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
#include <boost/log/attributes.hpp>
#include <boost/log/common.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <iostream>
#include <bitcoin/explorer.hpp>

BC_USE_LIBBITCOIN_MAIN

namespace logging = boost::log;

boost::log::formatting_ostream& operator<<(
    boost::log::formatting_ostream& strm,
    boost::log::to_log_manip<libbitcoin::log::severity> const& manip)
{
    strm.stream() << manip.get();
    return strm;
}

/**
 * Invoke this program with the raw arguments provided on the command line.
 * All console input and output streams for the application originate here.
 * @param argc  The number of elements in the argv array.
 * @param argv  The array of arguments, including the process.
 * @return      The numeric result to return via console exit.
 */
int bc::main(int argc, char* argv[])
{
    logging::add_file_log(
        logging::keywords::file_name = "debug",
        logging::keywords::format = (
            logging::expressions::stream << "["
                << logging::expressions::format_date_time<boost::posix_time::ptime, char>(
                    bc::log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
                << "][" << bc::log::attributes::channel
                << "][" << bc::log::attributes::severity
                << "]: " << logging::expressions::smessage
        ));

    auto error_filter = (bc::log::attributes::severity == bc::log::severity::warning)
        || (bc::log::attributes::severity == bc::log::severity::error)
        || (bc::log::attributes::severity == bc::log::severity::fatal);

    boost::log::add_file_log(
        logging::keywords::file_name = "error",
        logging::keywords::filter = error_filter,
        logging::keywords::format = (
            logging::expressions::stream << "["
                << logging::expressions::format_date_time<boost::posix_time::ptime, char>(
                    bc::log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
                << "][" << bc::log::attributes::channel
                << "][" << bc::log::attributes::severity
                << "]: " << logging::expressions::smessage
        ));

    boost::log::add_console_log(
        std::cout,
        boost::log::keywords::filter = (bc::log::attributes::severity == bc::log::severity::info),
        boost::log::keywords::format = (
            logging::expressions::stream << "["
                << logging::expressions::format_date_time<boost::posix_time::ptime, char>(
                    bc::log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
                << "][" << bc::log::attributes::channel
                << "][" << bc::log::attributes::severity
                << "]: " << logging::expressions::smessage
        ));

    boost::log::add_console_log(
        std::cerr,
        boost::log::keywords::filter = error_filter,
        boost::log::keywords::format = (
            logging::expressions::stream << "["
                << logging::expressions::format_date_time<boost::posix_time::ptime, char>(
                    bc::log::attributes::timestamp.get_name(), "%Y-%m-%d %H:%M:%S")
                << "][" << bc::log::attributes::channel
                << "][" << bc::log::attributes::severity
                << "]: " << logging::expressions::smessage
        ));

    return bc::explorer::dispatch(argc, const_cast<const char**>(argv),
        bc::cin, bc::cout, bc::cerr);
}
