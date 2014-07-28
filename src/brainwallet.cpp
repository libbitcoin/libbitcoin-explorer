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
#include <sx/command/brainwallet.hpp>

#include <iostream>
#include <sx/utility/utility.hpp>

using namespace sx;
using namespace sx::extension;

console_result brainwallet::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto algorithm = get_algorithm_option();
    auto password = get_password_argument();
    auto username = get_username_argument();

    cerr << SX_BRAINWALLET_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import  sys, subprocess, hashlib
//PIPE = subprocess.PIPE
//
//def runcmd(args,inp=''):
//    p = subprocess.Popen(args, stdout=PIPE, stdin=PIPE, stderr=PIPE)
//    return p.communicate(input=inp)[0]
//
//args, opts = [], {}
//i = 1
//while i < len(sys.argv):
//    if sys.argv[i][0:2] == '--':
//        opts[sys.argv[i][2:]] = sys.argv[i+1]
//        i += 2
//    else:
//        args.append(sys.argv[i])
//        i += 1
//
//if len(args) == 0: seed = ''
//elif len(args) == 1: seed = args[0]
//else: seed = args[0] + ':' + args[1]
//
//def bitcoin256(x): return hashlib.bitcoin256(x).hexdigest()
//
//def slowsha(x,rounds=1000):
//    old, new = x, ''
//    for i in range(rounds):
//        new = hashlib.bitcoin256(old).digest()
//        old = new+x
//    return new.encode('hex')
//
//if opts.get('algo','') == 'slowsha': algo = slowsha
//elif opts.get('rounds',None): algo = lambda x: slowsha(x,int(opts['rounds']))
//else: algo = bitcoin256
//
//print runcmd(['sx','base58check-encode',algo(seed),'128']).strip()
