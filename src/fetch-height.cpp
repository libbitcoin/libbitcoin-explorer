/**
 * Copyright (c) 2011-2014 sx developers (see AUTHORS)
 *
 * This file is part of sx.
 *
 * sx is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License with
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
#include <sx/command/fetch-height.hpp>

#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <obelisk/obelisk.hpp>
#include <sx/obelisk_client.hpp>
#include <sx/utility/utility.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extension;

static bool stopped;
static console_result result;

static void last_height_fetched(const std::error_code& error, size_t height)
{
    if (error)
    {
        std::cerr << error.message() << std::endl;
        result = console_result::failure;
    }
    else
        std::cout << height << std::endl;

    stopped = true;
}

console_result fetch_height::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    stopped = false;
    result = console_result::okay;

    obelisk_client client(*this);
    auto& fullnode = client.get_fullnode();
    fullnode.blockchain.fetch_last_height(last_height_fetched);
    client.poll(stopped);

    return result;
}

