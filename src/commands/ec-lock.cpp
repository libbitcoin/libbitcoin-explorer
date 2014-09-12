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
#include <bitcoin/explorer/commands/ec-lock.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result ec_lock::invoke(std::ostream& output, std::ostream& error)
{
    // Bound parameters.
    //const auto& secret = get_ec_private_key_argument();
    //const auto& passphrase = get_passphrase_argument();

    // TODO: implement BIP38

    error << BX_EC_LOCK_NOT_IMPLEMENTED << std::endl;
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
//def bitcoin256(x): return hashlib.bitcoin256(x).base16digest()
//
//def slowsha(x,rounds=1000):
//    old, new = x, ''
//    for i in range(rounds):
//        new = hashlib.bitcoin256(old).digest()
//        old = new+x
//    return new.encode('base16')
//
//if opts.get('algo','') == 'slowsha': algo = slowsha
//elif opts.get('rounds',None): algo = lambda x: slowsha(x,int(opts['rounds']))
//else: algo = bitcoin256
//
//print runcmd(['sx','base58check-encode',algo(seed),'128']).strip()
