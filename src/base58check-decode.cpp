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
#include <sx/command/base58check-decode.hpp>

#include <sx/command/base58-decode.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/dispatch.hpp>
#include <sx/utility/console.hpp>

using namespace sx;
using namespace sx::extension;

console_result base58check_decode::invoke(std::istream& input, 
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto base58check = get_base58check_argument();

    // TODO: invoke functionality from base58-decode >> unwrap.
    cerr << SX_BASE58CHECK_DECODE_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import subprocess, sys
//PIPE = subprocess.PIPE
//p = subprocess.Popen(['sx','base58-decode']+sys.argv[1:], stdout=PIPE, stdin=PIPE, stderr=PIPE)
//med = p.communicate(input=sys.stdin.read() if len(sys.argv) == 1 else '')[0]
//p2 = subprocess.Popen(['sx','unwrap',med], stdout=PIPE, stdin=PIPE, stderr=PIPE)
//print p2.communicate(input='')[0].strip()
