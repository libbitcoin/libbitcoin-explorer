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

#include <bitcoin/explorer/display.hpp>

#include <algorithm>
#include <format>
#include <bitcoin/explorer/define.hpp>
#include <bitcoin/explorer/dispatch.hpp>
#include <bitcoin/explorer/generated.hpp>
#include <bitcoin/explorer/utility.hpp>
#include <bitcoin/explorer/version.hpp>

namespace libbitcoin {
namespace explorer {

using namespace bc::system::config;

#define BX_HOME_PAGE_URL "https://github.com/libbitcoin/libbitcoin-explorer"

void display_command_names(std::ostream& stream)
{
    constexpr size_t width = 73;
    constexpr size_t gap = 2;

    system::string_list names{};
    const auto func = [&names](std::shared_ptr<command> explorer_command)
    {
        BC_ASSERT(explorer_command != nullptr);
        if (!explorer_command->obsolete())
            names.push_back(explorer_command->name());
    };

    broadcast(func);

    size_t longest{};
    for (const auto& name: names)
        longest = std::max(longest, name.length());

    const auto column = longest + gap;
    const auto columns = std::max(one, (width + gap) / column);
    const auto rows = system::ceilinged_divide(names.size(), columns);

    for (size_t row = 0; row < rows; ++row)
    {
        for (auto index = row; index < names.size(); index += rows)
        {
            if (index + rows < names.size())
                stream << std::format("{:<{}}", names.at(index), column);
            else
                stream << names.at(index);
        }

        stream << std::endl;
    }
}

void display_connection_failure(std::ostream& stream, const endpoint& url)
{
    stream << std::format(BX_CONNECTION_FAILURE, url.to_string()) << std::endl;
}

void display_invalid_command(std::ostream& stream, const std::string& command,
    const std::string& superseding)
{
    if (superseding.empty())
        stream << std::format(BX_INVALID_COMMAND, command);
    else
        stream << std::format(BX_DEPRECATED_COMMAND, command, superseding);

    stream << std::endl;
}

// English only hack to patch missing option name in an exception message.
static std::string fixup_option_message(const std::string& what)
{
    std::string message(what);
    system::replace(message, "for option is invalid", "is invalid");
    return message;
}

void display_invalid_parameter(std::ostream& stream,
    const std::string& message)
{
    stream << std::format(BX_INVALID_PARAMETER,
        fixup_option_message(message)) << std::endl;
}

void display_usage(std::ostream& stream)
{
    stream
        << std::endl << BX_COMMAND_USAGE << std::endl
        << std::endl << std::format(BX_VERSION_MESSAGE,
            LIBBITCOIN_EXPLORER_VERSION) << std::endl
        << std::endl << BX_COMMANDS_HEADER << std::endl
        << std::endl;

    display_command_names(stream);

    stream
        << std::endl << BX_COMMANDS_HOME_PAGE << std::endl
        << std::endl << BX_HOME_PAGE_URL << std::endl;
}

} // namespace explorer
} // namespace libbitcoin
