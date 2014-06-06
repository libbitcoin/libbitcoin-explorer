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
#include <iostream>
#include <bitcoin/bitcoin.hpp>
#include <sx/command/showscript.hpp>
#include <sx/utility/console.hpp>

using namespace bc;
using namespace sx;
using namespace sx::extensions;

console_result showscript::invoke(int argc, const char* argv[])
{
    if (!validate_argument_range(argc, example(), 1, 1))
        return console_result::failure;

    const auto raw_script = decode_hex(read_stream(std::cin));
    script_type script;
    try
    {
        script = parse_script(raw_script);
    }
    catch (end_of_stream)
    {
        std::cerr << "showscript: Error: Bad script." << std::endl;
        return console_result::failure;
    }

    std::cout << pretty(script) << std::endl;
    return console_result::okay;
}