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
#ifndef BX_UTILITY_IPP
#define BX_UTILITY_IPP

#include <iostream>
#include <string>
#include <boost/any.hpp>
#include <boost/program_options.hpp>
#include <bitcoin/explorer/define.hpp>

namespace libbitcoin {
namespace explorer {

template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input)
{
    if (variables.find(name) == variables.cend())
        if (!system::deserialize(parameter, input))
            throw istream_exception(name);
}

template <typename Value>
void load_path(Value& parameter, const std::string& name,
    po::variables_map& variables)
{
    // The path is not set as an argument so we can't load from file.
    auto variable = variables.find(name);
    if (variable == variables.cend())
        return;

    // Get the argument value as a string.
    // boost: overloads taking an any pointer do not throw.
    const auto path = boost::any_cast<std::string>(variable->second.value());

    // The path is the stdio sentinal, so clear parameter and don't read file.
    if (path == BX_STDIO_PATH_SENTINEL)
    {
        variables.erase(variable);
        return;
    }

    system::ifstream file(path, std::ios::binary);
    if (!file.good() || !system::deserialize(parameter, file))
        throw istream_exception(path);
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
        system::ofstream file(path, std::ofstream::binary);
        file << instance;
        if (terminate)
            file << std::endl;
    }
}

} // namespace explorer
} // namespace libbitcoin

#endif
