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
#include <sx/command/satoshi.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/dispatch.hpp>
#include <sx/utility/console.hpp>

using namespace sx;
using namespace sx::extension;

console_result satoshi::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto algorithm = get_btc_argument();

    // TODO: parse and validate input and multiply by 10^8.
    cerr << SX_SATOSHI_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import sys
//from decimal import Decimal as D
//
//if len(sys.argv) != 2:
//    print >> sys.stderr, "Usage: sx satoshi BTC"
//    sys.exit(-1)
//print "%.0f" % (D(sys.argv[1]) * D(10) ** 8)
//sys.exit(0)
//
