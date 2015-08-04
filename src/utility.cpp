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
#include <bitcoin/explorer/utility.hpp>

#include <iomanip>
#include <iostream>
#include <random>
#include <cstdint>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>
#include <vector>
#include <boost/date_time.hpp>
#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/info_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace boost::posix_time;
using namespace bc::client;
using boost::filesystem::path;
using boost::format;

namespace libbitcoin {
namespace explorer {

// Guard against concurrent file writes.
static std::mutex logfile_mutex;

static void output_to_file(std::ofstream& file, log_level level, 
    const std::string& domain, const std::string& body)
{
    static const auto form = "%1% %2% [%3%] %4%\n";
    if (!body.empty())
    {
        const auto log = level_repr(level);
        const auto time = microsec_clock::local_time().time_of_day();
        const auto message = (format(form) % time % log % domain % body).str();

        std::lock_guard<std::mutex> lock_logfile(logfile_mutex);
        file << message;
        file.flush();
    }
}

// Bind the global debug logging context.
void bind_debug_log(std::ofstream& debug)
{
    log_debug().set_output_function(
        std::bind(output_to_file, std::ref(debug),
        ph::_1, ph::_2, ph::_3));

    log_info().set_output_function(
        std::bind(output_to_file, std::ref(debug),
        ph::_1, ph::_2, ph::_3));
}

// Bind the global error logging context.
void bind_error_log(std::ofstream& error)
{
    log_warning().set_output_function(
        std::bind(output_to_file, std::ref(error),
        ph::_1, ph::_2, ph::_3));

    log_error().set_output_function(
        std::bind(output_to_file, std::ref(error),
        ph::_1, ph::_2, ph::_3));

    log_fatal().set_output_function(
        std::bind(output_to_file, std::ref(error),
        ph::_1, ph::_2, ph::_3));
}

bool is_base2(const std::string& text)
{
    for (const auto& character: text)
        if (character != '0' && character != '1')
            return false;

    return true;
}

bool is_testnet(const std::string& network)
{
    return network == BX_TESTNET;
}

connection_type get_connection(const command& cmd)
{
    const auto connect_timeout_milliseconds = period_ms(
        cmd.get_general_connect_timeout_seconds_setting() * 1000);

    if (is_testnet(cmd.get_general_network_setting()))
        return connection_type
        {
            cmd.get_general_connect_retries_setting(),
            connect_timeout_milliseconds,
            cmd.get_testnet_cert_file_setting(),
            cmd.get_testnet_url_setting(),
            cmd.get_testnet_server_cert_key_setting()
        };
    else return connection_type
        {
            cmd.get_general_connect_retries_setting(),
            connect_timeout_milliseconds,
            cmd.get_mainnet_cert_file_setting(),
            cmd.get_mainnet_url_setting(),
            cmd.get_mainnet_server_cert_key_setting()
        };
}

// The key may be invalid, caller may test for null secret.
ec_secret new_key(data_slice seed)
{
    // The testnet value is not relevant to the secret.
    constexpr bool testnet = false;

    // This is retained in order to preserve test cases and docs.
    // Using HD key generation because we don't have helper for EC.
    const hd_private_key hd_key(seed, testnet);

    if (!hd_key.valid())
    {
        // bc::cerr << "You just won the lottery!" << std::endl;
        return ec_secret();
    }

    return hd_key.private_key();
}

// Not testable due to lack of random engine injection.
data_chunk new_seed(size_t bitlength)
{
    size_t fill_seed_size = bitlength / byte_bits;
    data_chunk seed(fill_seed_size);
    random_fill(seed);
    return seed;
}

// Not testable due to lack of clock injection.
ptime now()
{
    using namespace boost::posix_time;
    ptime local_time_in_seconds(second_clock::local_time());
    return local_time_in_seconds;
}

std::vector<std::string> numbers_to_strings(const index_list& indexes)
{
    std::vector<std::string> stringlist;
    for (const auto& index: indexes)
        stringlist.push_back(std::to_string(index));

    return stringlist;
}

// Not testable due to lack of random engine injection.
// DEPRECATED in favor of libbitcoin::pseudo_random_fill.
void random_fill(data_chunk& chunk)
{
    pseudo_random_fill(chunk);
}

// TODO: switch to binary for raw (primitive) reads in windows.
std::string read_stream(std::istream& stream)
{
    std::istreambuf_iterator<char> first(stream), last;
    std::string result(first, last);
    return result;
}

script_type script_to_raw_data_script(const script_type& script)
{
    return raw_data_script(save_script(script));
}

name_value_pairs split_pairs(const std::vector<std::string> tokens,
    const std::string delimiter)
{
    name_value_pairs list;

    for (const auto& token: tokens)
    {
        const auto words = split(token, delimiter);

        const auto& left = words[0];
        std::string right;
        if (words.size() > 1)
            right = words[1];

        list.push_back(std::make_pair(left, right));
    }

    return list;
}

// Not unit testable (sleep).
void sleep_ms(uint32_t milliseconds)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}

bool starts_with(const std::string& value, const std::string& prefix)
{
    try
    {
        return boost::istarts_with(value, prefix);
    }
    catch (boost::bad_lexical_cast)
    {
        return false;
    }
}

bool unwrap(wrapped_data& data, data_slice wrapped)
{
    return bc::unwrap(data.version, data.payload, data.checksum, wrapped);
}

data_chunk wrap(const wrapped_data& data)
{
    return bc::wrap(data.version, data.payload);
}

// We aren't yet using a reader, although it is possible using ptree.
std::ostream& write_stream(std::ostream& output, const pt::ptree& tree,
    encoding_engine engine)
{
    switch (engine)
    {
        case encoding_engine::json:
            pt::write_json(output, tree);
            break;
        case encoding_engine::xml:
            pt::write_xml(output, tree);

            // property tree XML serialization doesn't terminate the string.
            output << std::endl;

            break;
        default:
            pt::write_info(output, tree);
            break;
    }

    return output;
}

} // namespace explorer
} // namespace libbitcoin
