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
#include <sx/command/fetch-height-bci.hpp>

#include <iostream>
#include <sx/utility/utility.hpp>

using namespace sx;
using namespace sx::extension;

console_result fetch_height_bci::invoke(std::ostream& output,
    std::ostream& cerr)
{
    // TODO: integrate cpp-netlib (without ssl).
    cerr << SX_FETCH_HEIGHT_BCI_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//
//import urllib, urllib2, json, sys, random
//
//opener = urllib2.build_opener()
//opener.addheaders = [('User-agent', 'Mozilla/5.0'+str(random.randrange(1000000)))]
//
//text = opener.open('http://blockchain.info/latestblock').read()
//
//try:
//    jsonobj = json.loads(text)
//    print jsonobj["height"]
//except:
//    sys.stderr.write("Bad JSON")
//    sys.exit(-1)
