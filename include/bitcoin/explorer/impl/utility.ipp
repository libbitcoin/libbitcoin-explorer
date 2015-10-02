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
#ifndef BX_UTILITY_IPP
#define BX_UTILITY_IPP

#ifdef _MSC_VER
// Suppressing msvc warnings from boost that are heard to deal with
// because boost/algorithm carelessly defines _SCL_SECURE_NO_WARNINGS
// without sampling it first. 
#pragma warning(push)
#pragma warning(disable : 4996)
#endif
#include <cstddef>
#include <iostream>
#include <cstdint>
#include <string>
#include <system_error>
#include <tuple>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <boost/range/algorithm/find_if.hpp>
#include <boost/lexical_cast.hpp>
#ifdef _MSC_VER
#pragma warning(pop)
#endif
#include <bitcoin/bitcoin.hpp>
#include <bitcoin/explorer/define.hpp>

/* NOTE: don't declare 'using namespace foo' in headers. */

namespace libbitcoin {
namespace explorer {

template <typename Value>
void deserialize(Value& value, const std::string& text, bool trim)
{
    if (trim)
        value = boost::lexical_cast<Value>(boost::trim_copy(text));
    else
        value = boost::lexical_cast<Value>(text);
}

template <typename Value>
void deserialize(Value& value, std::istream& input, bool trim)
{
    deserialize(value, read_stream(input), trim);
}

template <typename Value>
void deserialize(std::vector<Value>& collection, const std::string& text,
    bool trim)
{
    // This had problems with the inclusion of the ideographic (CJK) space 
    // (0xe3,0x80, 0x80). Need to infuse the local in bc::split().
    const auto tokens = split(text, " \n\r\t");
    for (const auto& token: tokens)
    {
        Value value;
        deserialize(value, token, true);
        collection.push_back(value);
    }
}

template <typename Item>
bool deserialize_satoshi_item(Item& item, const data_chunk& data)
{
    return item.from_data(data);
}

template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input, bool raw)
{
    if (variables.find(name) == variables.end())
        deserialize(parameter, input, !raw);
}

template <typename Value>
void load_path(Value& parameter, const std::string& name,
    po::variables_map& variables, bool raw)
{
    // The path is not set as an argument so we can't load from file.
    auto variable = variables.find(name);
    if (variable == variables.end())
        return;

    // Get the argument value as a string.
    const auto path = boost::any_cast<std::string>(variable->second.value());
    
    // The path is the stdio sentinal, so clear parameter and don't read file.
    if (path == BX_STDIO_PATH_SENTINEL)
    {
        variables.erase(variable);
        return;
    }

    bc::ifstream file(path, std::ios::binary);
    if (!file.good())
    {
        BOOST_THROW_EXCEPTION(po::invalid_option_value(path));
    }

    deserialize(parameter, file, !raw);
}

template <typename Value>
std::string serialize(const Value& value, const std::string& fallback)
{
    std::stringstream stream;
    stream << value;
    const auto& text = stream.str();
    return text.empty() ? fallback : text;
}

template <typename Item>
data_chunk serialize_satoshi_item(const Item& item)
{
    return item.to_data();
}

template <typename Instance>
void write_file(std::ostream& output, const std::string& path,
    const Instance& instance, bool terminate)
{        
    if (path.empty() || path == BX_STDIO_PATH_SENTINEL)
    {
        output << instance;
        if (terminate)
            output << std::endl;
    }
    else
    {
        bc::ofstream file(path, std::ofstream::binary);
        file << instance;
        if (terminate)
            file << std::endl;
    }
}

} // namespace explorer
} // namespace libbitcoin

#endif
