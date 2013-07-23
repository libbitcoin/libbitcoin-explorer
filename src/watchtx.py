#!/usr/bin/python
import zmq
import hashlib
import sys

def hash_transaction(data):
    return hashlib.sha256(hashlib.sha256(data).digest()).digest()[::-1]

def watch(connection, watch_hashes):
    if not watch_hashes:
        print >> sys.stderr, "No valid transaction hashes to watch."
        return
    context = zmq.Context(1)
    socket = context.socket(zmq.SUB)
    socket.connect(connection)
    socket.setsockopt(zmq.SUBSCRIBE, "")
    while watch_hashes:
        tx_hash = socket.recv()
        tx_data = socket.recv()
        assert hash_transaction(tx_data) == tx_hash
        print "Transaction (%s bytes): %s" % (
            len(tx_data), tx_hash.encode("hex"))
        if tx_hash in watch_hashes:
            print "***********************"
            print "* Transaction Found ! *"
            print "***********************"
            watch_hashes.remove(tx_hash)
        #print tx_data.encode("hex")

def convert_hashes(args):
    watch_hashes = set()
    for tx_hex in sys.argv[1:]:
        try:
            # decode can raise TypeError
            tx_hash = tx_hex.decode("hex")
            if len(tx_hash) != 32:
                raise TypeError
        except TypeError:
            print >> sys.stderr, "Skipping invalid hash: %s" % tx_hex
        else:
            print "Watching: %s" % tx_hex
            watch_hashes.add(tx_hash)
    return watch_hashes

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print >> sys.stderr, "Usage: watchtx TXHASH1 TXHASH2 ..."
    else:
        hashes = convert_hashes(sys.argv[1:])
        watch("tcp://localhost:9094", hashes)

