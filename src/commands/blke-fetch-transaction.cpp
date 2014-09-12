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
#include <bitcoin/explorer/commands/blke-fetch-transaction.hpp>

#include <iostream>
#include <bitcoin/explorer/define.hpp>

using namespace bc::explorer;
using namespace bc::explorer::commands;

console_result blke_fetch_transaction::invoke(std::ostream& output,
    std::ostream& error)
{
    error << BX_BLKE_FETCH_TRANSACTION_OBSOLETE << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import urllib, urllib2, sys, json, copy, random, subprocess
//PIPE = subprocess.PIPE
//
//def runcmd(args,inp=''):
//    p = subprocess.Popen(args, stdout=PIPE, stdin=PIPE, stderr=PIPE)
//    return p.communicate(input=inp)[0]
//
//opener = urllib2.build_opener()
//opener.addheaders = [('User-agent', 'Mozilla/5.0'+str(random.randrange(1000000)))]
//
//def process_script(scr):
//    if scr == '': return []
//    inp,o = scr.split(' '),[]
//    for i in range(len(inp)):
//        if inp[i] == '0': o.append('zero')
//        elif inp[i][:3] == 'OP_': o.append(inp[i][3:].lower())
//        else: o.extend(['[',inp[i],']'])
//    return o
//
//try:
//    data = opener.open('http://blockexplorer.com/rawtx/' + sys.argv[1]).read()
//    j = json.loads(data)
//except:
//    sys.stderr.write("Transaction not found")
//    sys.exit(-1)
//
//ins,outs = [],[]
//for inp in j["in"]:
//    if "scriptSig" in inp:
//        scriptSig = runcmd(["sx","rawscript"]+process_script(inp.get("scriptSig",""))).strip()
//    else:
//        scriptSig = inp["coinbase"]
//    ins.append({
//        "prev": inp["prev_out"]["hash"]+':'+str(inp["prev_out"]["n"]),
//        "script": scriptSig
//    })
//for out in j["out"]:
//    script = process_script(out["scriptPubKey"])
//    raw = runcmd(['sx','rawscript']+script).strip()
//    outs.append({
//        "value": int(out["value"].replace('.',''))
//    })
//    if script[0] == 'dup' and script[1] == 'hash160':
//        outs[-1]["address"] = runcmd(['sx','encode-addr'],script[3]).strip()
//    else:
//        outs[-1]["address"] = runcmd(['sx','base58check-encode']+[script[2],'5']).strip()
//filename = '/tmp/sx-'+str(random.randrange(10**9))
//cmd = ["sx","mktx",filename]
//for i in ins: cmd += ['-i',i["prev"]]
//for o in outs: cmd += ['-o',o["address"]+":"+str(o["value"])]
//runcmd(cmd)
//for i in range(len(ins)): 
//    newtx = runcmd(["sx","set-input",filename,str(i)],ins[i]["script"]).strip()
//    open(filename,'w').write(newtx)
//print open(filename,'r').read()
