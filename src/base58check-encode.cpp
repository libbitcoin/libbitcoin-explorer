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
#include <sx/command/base58-encode.hpp>
#include <sx/command/base58check-encode.hpp>
#include <sx/command/wrap.hpp>
#include <sx/dispatch.hpp>
#include <sx/utility/console.hpp>

using namespace sx;
using namespace sx::extensions;

console_result base58check_encode::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // TODO: invoke functionality from wrap >> base58-encode.
    cerr << SX_BASE58CHECK_ENCODE_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import subprocess, sys
//PIPE = subprocess.PIPE
//p = subprocess.Popen(['sx','wrap']+sys.argv[1:], stdout=PIPE, stdin=PIPE, stderr=PIPE)
//med = p.communicate(input=sys.stdin.read() if len(sys.argv) < 3 else '')[0]
//p2 = subprocess.Popen(['sx','base58-encode',med], stdout=PIPE, stdin=PIPE, stderr=PIPE)
//print p2.communicate(input='')[0].strip()
