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
//#include <sstream>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/json_parser.hpp>
#include <sx/command/bci-history.hpp>
#include <sx/command/unwrap.hpp>
#include <sx/dispatch.hpp>
#include <sx/utility/console.hpp>

using namespace sx;
using namespace sx::extension;

console_result bci_history::invoke(std::istream& input,
    std::ostream& output, std::ostream& cerr)
{
    // Bound parameters.
    auto address = get_address_argument();

    cerr << SX_BCI_HISTORY_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import urllib, urllib2, sys, json, copy, random
//
//addrs = sys.argv[1:]
//
//opener = urllib2.build_opener()
//opener.addheaders = [('User-agent', 'Mozilla/5.0'+str(random.randrange(1000000)))]
//
//data = [opener.open('http://blockchain.info/address/%s?format=json' % s).read() for s in addrs]
//
//jsonobj = []
//for x in data:
//    try:
//        jsonobj.append(json.loads(x))
//    except:
//        sys.stderr.write(x)
//        sys.exit(-1)
//
//def addarrays(arrs): return reduce(lambda x,y: x+y,arrs,[])
//
//txs = addarrays([x["txs"] for x in jsonobj])
//
//def extend(obj,key,val):
//    o = copy.copy(obj)
//    o[key] = val
//    return o
//
//def get_outputs(tx):
//    return [extend(o,'output', tx["hash"]+":"+str(o["n"])) for o in tx["out"]]
//
//def get_spends(tx):
//    def format_spend(inp,ind):
//        return extend(inp["prev_out"], 'input', tx["hash"]+":"+str(ind))
//
//    return [format_spend(inp,ind) for ind,inp in enumerate(tx["inputs"])]
//
//
//def key(a): return (a["tx_index"],a["n"])
//
//outs = addarrays([get_outputs(tx) for tx in txs])
//myouts = sorted([o for o in outs if o["addr"] in addrs],key=key)
//
//#for o in myouts:
//#    print "o:     ",o
//
//spends = addarrays([get_spends(tx) for tx in txs])
//myspends = sorted([o for o in spends if o["addr"] in addrs],key=key)
//
//#for s in myspends:
//#    print "s:     ",s
//
//utxo = []
//stxo = []
//
//i,j = 0,0
//
//while i < len(myouts) and j < len(myspends):
//    if i > 0 and key(myouts[i]) == key(myouts[i-1]):
//        i += 1
//    elif j > 0 and key(myspends[j]) == key(myspends[j-1]):
//        j += 1
//    elif key(myouts[i]) < key(myspends[j]):
//        myouts[i]["spend"] = "Unspent"
//        utxo.append(myouts[i])
//        i += 1
//    elif key(myouts[i]) > key(myspends[j]):
//        j += 1
//    else:
//        myouts[i]["spend"] = myspends[j]["input"]
//        stxo.append(myouts[i])
//        i += 1
//        j += 1
//
//utxo.extend([extend(x,"spend","Unspent") for x in myouts[i:]])
//
//for txo in utxo+stxo:
//    print "Address: "+txo["addr"]
//    print "  output: "+txo["output"]
//    print "  value: "+str(txo["value"])
//    print "  spend: "+str(txo["spend"])
//    print ""
