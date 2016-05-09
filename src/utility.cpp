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

#include <algorithm>
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
#include <bitcoin/client.hpp>
#include <bitcoin/explorer/command.hpp>
#include <bitcoin/explorer/define.hpp>

using namespace boost::posix_time;
using namespace bc::client;
using boost::filesystem::path;

namespace libbitcoin {
namespace explorer {

bool is_base2(const std::string& text)
{
    for (const auto& character: text)
        if (character != '0' && character != '1')
            return false;

    return true;
}

connection_type get_connection(const command& cmd)
{
    return connection_type
    {
        cmd.get_server_connect_retries_setting(),
        cmd.get_server_connect_timeout_seconds_setting(),
        cmd.get_server_client_cert_file_setting(),
        cmd.get_server_url_setting(),
        cmd.get_server_server_cert_key_setting()
    };
}

// The key may be invalid, caller may test for null secret.
ec_secret new_key(const data_chunk& seed)
{
    const wallet::hd_private key(seed);
    return key.secret();
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

std::vector<std::string> numbers_to_strings(
    const bc::client::index_list& indexes)
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

// This verifies the checksum.
bool unwrap(wrapped_data& data, data_slice wrapped)
{
    if (!verify_checksum(wrapped))
        return false;

    data.version = wrapped.data()[0];
    const auto payload_begin = std::begin(wrapped) + 1;
    const auto checksum_begin = std::end(wrapped) - checksum_size;
    data.payload.resize(checksum_begin - payload_begin);
    std::copy(payload_begin, checksum_begin, data.payload.begin());
    data.checksum = from_little_endian_unsafe<uint32_t>(checksum_begin);
    return true;
}

// This recalculates the checksum, ignoring what is in data.checksum.
data_chunk wrap(const wrapped_data& data)
{
    auto bytes = to_chunk(data.version);
    extend_data(bytes, data.payload);
    append_checksum(bytes);
    return bytes;
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
