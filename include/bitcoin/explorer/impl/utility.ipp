/**
 * Copyright (c) 2011-2019 libbitcoin developers (see AUTHORS)
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
#include <bitcoin/client.hpp>

namespace libbitcoin {
namespace explorer {

template <typename Command>
client::connection_settings get_connection(const Command& command)
{
    return
    {
        command.get_server_connect_retries_setting(),
        command.get_server_url_setting(),
        command.get_server_block_url_setting(),
        command.get_server_transaction_url_setting(),
        command.get_server_socks_proxy_setting(),
        command.get_server_server_public_key_setting(),
        command.get_server_client_private_key_setting()
    };
}

template <typename Value>
void load_input(Value& parameter, const std::string& name,
    po::variables_map& variables, std::istream& input, bool raw)
{
    if (variables.find(name) == variables.end())
        if (!system::deserialize(parameter, input, !raw))
            throw istream_failure(name);
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

    system::ifstream file(path, std::ios::binary);
    if (!file.good() || !system::deserialize(parameter, file))
        throw istream_failure(path);
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
