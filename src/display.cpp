/**
 * Copyright (c) 2011-2014 libbitcoin developers (see AUTHORS)
 *
 * This file is part of libbitcoin_explorer.
 *
 * libbitcoin_explorer is free software: you can redistribute it and/or
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
// #include "precompile.hpp"
#include <bitcoin/explorer/display.hpp>

#include <iostream>
#include <bitcoin/explorer/dispatch.hpp>
#include <bitcoin/explorer/utility/utility.hpp>

// TODO: once these settle down make testable through stream injection.

namespace libbitcoin {
namespace explorer {

void display_invalid_command(const std::string& command)
{
    std::cerr << "sx: " << command
        << " is not a sx option or command. See 'sx --help'." << std::endl;
}

void display_invalid_config(const std::string& file)
{
    std::cerr << "sx: config file '" << file << "' doesn't exist!" 
        << std::endl;
}

void display_invalid_variables(const std::string& message)
{
    std::cerr << "sx: " << message << std::endl;
}

void display_line()
{
    std::cout << std::endl;
}

void display_usage()
{
    std::cerr << "Usage: sx COMMAND [ARGS]..." << std::endl;
    std::cerr << std::endl;
    std::cerr << "  -c, --config               "
        "Specify a config file" << std::endl;
    std::cerr << std::endl;
    std::cerr << "The sx commands are:" << std::endl;
    std::cerr << std::endl;

    // TODO: sort commands and organize streamed output.
    dispatch_usage();

    std::cerr << std::endl;
    std::cerr << "See 'sx help COMMAND' for more information "
        "on a specific command." << std::endl;
    std::cerr << std::endl;
    std::cerr << "SX home page: <http://sx.dyne.org/>" << std::endl;
}

bool display_usage(const std::shared_ptr<command> command)
{
    std::cerr << "Not Implemented" << std::endl;
    return true;
}


} // namespace explorer
} // namespace libbitcoin
