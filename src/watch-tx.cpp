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
#include <sx/command/watch-tx.hpp>

#include <iostream>
#include <sx/utility/utility.hpp>

using namespace sx;
using namespace sx::extension;

console_result watch_tx::invoke(std::istream& input, std::ostream& output,
    std::ostream& cerr)
{
    // Bound parameters.
    const auto hashes = get_hashs_argument();

    cerr << SX_WATCH_TX_NOT_IMPLEMENTED << std::endl;
    return console_result::failure;
}

//#!/usr/bin/python
//import hashlib
//import sys
//try:
//    import zmq
//except ImportError:
//    print >> sys.stderr, "Please install Python ZeroMQ for this tool to work."
//    print >> sys.stderr, ""
//    print >> sys.stderr, "  $ sudo apt-get install python-zmq"
//    print >> sys.stderr, ""
//    sys.exit(1)
//
//def config_value(filename, option_key, default=""):
//    try:
//        rawfile = open(filename).read()
//    except IOError:
//        print >> sys.stderr, "Config file '%s' does not exist!" % filename
//        return default
//    lines = [line.strip() for line in rawfile.split("\n")]
//    extract_pair = lambda line: \
//        [token.strip() for token in line.split("=", 1)]
//    key_values = [extract_pair(line) for line in lines
//                  if len(extract_pair(line)) == 2]
//    key_values = [(key, value.strip('"')) for key, value in key_values]
//    lookup = dict(key_values)
//    try:
//        return lookup[option_key]
//    except KeyError:
//        return default
//
//def hash_transaction(data):
//    return hashlib.sha256(hashlib.sha256(data).digest()).digest()[::-1]
//
//def watch(connection, watch_hashes):
//    if not watch_hashes:
//        print >> sys.stderr, "No valid transaction hashes to watch."
//        return
//    context = zmq.Context(1)
//    socket = context.socket(zmq.SUB)
//    socket.connect(connection)
//    socket.setsockopt(zmq.SUBSCRIBE, "")
//    while watch_hashes:
//        tx_hash = socket.recv()
//        tx_data = socket.recv()
//        assert hash_transaction(tx_data) == tx_hash
//        print "Transaction (%s bytes): %s" % (
//            len(tx_data), tx_hash.encode("hex"))
//        if tx_hash in watch_hashes:
//            print "***********************"
//            print "* Transaction Found ! *"
//            print "***********************"
//            watch_hashes.remove(tx_hash)
//        #print tx_data.encode("hex")
//
//def convert_hashes(args):
//    watch_hashes = set()
//    for tx_hex in sys.argv[1:]:
//        try:
//            # decode can raise TypeError
//            tx_hash = tx_hex.decode("hex")
//            if len(tx_hash) != 32:
//                raise TypeError
//        except TypeError:
//            print >> sys.stderr, "Skipping invalid hash: %s" % tx_hex
//        else:
//            print "Watching: %s" % tx_hex
//            watch_hashes.add(tx_hash)
//    return watch_hashes
//
//if __name__ == "__main__":
//    if len(sys.argv) < 2:
//        print >> sys.stderr, "Usage: watchtx TXHASH1 TXHASH2 ..."
//    else:
//        hashes = convert_hashes(sys.argv[1:])
//        connection = config_value("/etc/sx.cfg", "service",
//                                  "tcp://localhost:9094")
//        watch(connection, hashes)
//
