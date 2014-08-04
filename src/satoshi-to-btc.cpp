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
#include <sx/command/satoshi-to-btc.hpp>

#include <iostream>
#include <sx/utility/utility.hpp>

using namespace sx;
using namespace sx::extension;

console_result satoshi_to_btc::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    const auto satoshi = get_satoshi_argument();

    // TODO: parse and validate input and multiply by 10^-8.
    // std::string bc::satoshi_to_btc(uint64_t value)
    cerr << SX_SATOSHI_TO_BTC_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import sys
//from decimal import Decimal as D
//
//if len(sys.argv) != 2:
//    print >> sys.stderr, "Usage: sx btc SATOSHIS"
//    sys.exit(-1)
//print "%.8f" % (D(sys.argv[1]) * D(10)**-8)
//sys.exit(0)
//
