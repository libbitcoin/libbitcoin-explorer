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
#include "precompile.hpp"
#include <sx/command/fetch-public-key.hpp>

#include <iostream>
#include <sx/define.hpp>

using namespace explorer;
using namespace explorer::commands;

console_result fetch_public_key::invoke(std::ostream& output,
    std::ostream& error)
{
    // Bound parameters.
    const auto& address = get_bitcoin_address_argument();

    error << SX_FETCH_PUBLIC_KEY_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import sys, re, os, subprocess
//
//if (len(sys.argv) != 2):
//    print >> sys.stderr, "Usage: sx get-pubkey ADDRESS"
//    sys.exit(-1)
//
//address=sys.argv[1]
//lines = os.popen('sx history '+address).readlines()
//
//# Convert to float or int if possible, otherwise leave as string
//def attempt_num(x):
//    if re.match('^(-|)[0-9]*(|\.[0-9]*)$',x): return float(x) if '.' in x else int(x)
//    else: return x
//
//# run a shell command with/out input string
//def run_command(command, input_str=None):
//    if input_str!=None:
//        p = subprocess.Popen(command, shell=True,
//            stdin=subprocess.PIPE,
//            stdout=subprocess.PIPE,
//            stderr=subprocess.STDOUT)
//        return p.communicate(input_str)
//    else:
//        p = subprocess.Popen(command, shell=True,
//            stdout=subprocess.PIPE,
//            stderr=subprocess.STDOUT)
//        return p.communicate()
//
//# verify on blockchain
//if len(lines) == 0:
//    print >> sys.stderr, "Address "+address+" was not found on the blockchain"
//    sys.exit(-1)
//
//# Create objects
//txo = []
//obj = {}
//for i in range(len(lines)):
//    indent = len(re.match('^ *',lines[i]).group(0))
//    fields = [x for x in lines[i].strip().split(' ') if x]
//    if len(fields) < 2:
//        continue
//    if indent == 0:
//        if obj: txo.append(obj)
//        obj = {}
//    obj[fields[0][:-1]] = attempt_num(fields[1])
//    obj["$txt"] = obj.get("$txt","") + lines[i]
//
//if obj: txo.append(obj)
//
//# look for spent tx
//stxo=''
//txid=''
//for x in txo:
//    if x["spend"] != "Unspent":
//        stxo=x["spend"]
//        break
//# if not found, report
//if stxo=='':
//    print >> sys.stderr, "Address "+address+" has no spent tx so no public key is available"
//    sys.exit(1)
//
//try:
//    txid=stxo.split(':')[0]
//except IndexError:
//    print >> sys.stderr, "Failure parsing txid of stxo for address "+address
//    sys.exit(1)
//
//# check the corresponding tx and retrieve the pubkey
//f = os.popen('sx fetch-transaction '+txid).read()
//parsed_tx=run_command('sx showtx', f)
//first_tx=parsed_tx[0]
//try:
//    script=first_tx.split('script:')[1].split('sequence:')[0]
//    if script.strip().startswith('zero'):
//        print >> sys.stderr, "Cannot get public key for script hash based address "+address
//        sys.exit(1)
//    print first_tx.split('script:')[1].split('sequence:')[0].split('[ ')[-1].split()[0]
//except IndexError:
//    print >> sys.stderr, "Cannot parse data for address "+address
//    sys.exit(1)
