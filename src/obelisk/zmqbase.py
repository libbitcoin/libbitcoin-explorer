import sys
import random
import struct

# Broken for ZMQ 4
#try:
#    from zmqproto import ZmqSocket
#except ImportError:
#    from zmq_fallback import ZmqSocket
from zmq_fallback import ZmqSocket

from obelisk.serialize import checksum

SNDMORE = 1

MAX_UINT32 = 4294967295

class ClientBase(object):

    valid_messages = []

    def __init__(self, address, block_address=None, tx_address=None, version=3):
        self._messages = []
        self._tx_messages = []
        self._block_messages = []
        self.zmq_version = version
        self.running = 1
        self._socket = self.setup(address)
        if block_address:
            self._socket_block = self.setup_block_sub(
                block_address, self.on_raw_block)
        if tx_address:
            self._socket_tx = self.setup_transaction_sub(
                tx_address, self.on_raw_transaction)
        self._subscriptions = {'address': {}}

    # Message arrived
    def on_raw_message(self, id, cmd, data):
        res = None
        short_cmd = cmd.split('.')[-1]
        if short_cmd in self.valid_messages:
            res = getattr(self, '_on_'+short_cmd)(data)
        else:
            print "Unknown Message", cmd
        if res:
            self.trigger_callbacks(id, *res)

    def on_raw_block(self, height, hash, header, tx_num, tx_hashes):
        print "block", height, len(tx_hashes)

    def on_raw_transaction(self, hash, transaction):
        print "tx", hash.encode('hex')

    # Base Api
    def send_command(self, command, data='', cb=None):
        tx_id = random.randint(0, MAX_UINT32)

        self.send('', SNDMORE)      # destination
        self.send(command, SNDMORE) # command
        self.send(struct.pack('I', tx_id), SNDMORE) # id (random)
        self.send(data, SNDMORE)    # data

        self.send(checksum(data), 0)    # checksum
        if cb:
            self._subscriptions[tx_id] = cb
        return tx_id

    def trigger_callbacks(self, tx_id, *args):
        if tx_id in self._subscriptions:
            self._subscriptions[tx_id](*args)
            del self._subscriptions[tx_id]

    # Low level zmq abstraction into obelisk frames
    def send(self, *args, **kwargs):
        self._socket.send(*args, **kwargs)

    def frame_received(self, frame, more):
        self._messages.append(frame)
        if not more:
            if not len(self._messages) == 5:
                print "Sequence with wrong messages", len(self._messages)
                print [m.encode("hex") for m in self._messages]
                self._messages = []
                return
            uuid, command, id, data, chksum = self._messages
            self._messages = []
            if checksum(data) == chksum:
                id = struct.unpack('I', id)[0]
                self.on_raw_message(id, command, data)
            else:
                print "bad checksum"

    def block_received(self, frame, more):
        self._block_messages.append(frame)
        if not more:
            nblocks = struct.unpack('Q', self._block_messages[3])[0]
            if not len(self._block_messages) == 4+nblocks:
                print "Sequence with wrong messages", len(self._block_messages), 4+nblocks
                self._block_messages = []
                return
            height, hash, header, tx_num = self._block_messages[:4]
            tx_hashes = self._block_messages[5:]
            if len(tx_num) >= 4:
                tx_num = struct.unpack_from('I', tx_num, 0 )[0]
            else:
                print "wrong tx_num length", len(tx_num), tx_num
                tx_num = struct.unpack('I', tx_num.zfill(4))[0]
            self._block_messages = []
            height = struct.unpack('I', height)[0]
            self._block_cb(height, hash, header, tx_num, tx_hashes)

    def transaction_received(self, frame, more):
        self._tx_messages.append(frame)
        if not more:
            if not len(self._tx_messages) == 2:
                print "Sequence with wrong messages", len(self._tx_messages)
                self._tx_messages = []
                return
            hash, transaction = self._tx_messages
            self._tx_messages = []
            self._tx_cb(hash, transaction)

    def setup(self, address):
        s = ZmqSocket(self.frame_received, self.zmq_version)
        s.connect(address)
        return s

    def setup_block_sub(self, address, cb):
        s = ZmqSocket(self.block_received, self.zmq_version, type='SUB')
        s.connect(address)
        self._block_cb = cb
        return s

    def setup_transaction_sub(self, address, cb):
        s = ZmqSocket(self.transaction_received, self.zmq_version, type='SUB')
        s.connect(address)
        self._tx_cb = cb
        return s

    # Low level packing
    def get_error(data):
        return struct.unpack_from('<I', data, 0)[0]

    def unpack_table(self, row_fmt, data, start=0):
        # get the number of rows
        row_size = struct.calcsize(row_fmt)
        nrows = (len(data)-start)/row_size

        # unpack
        rows = []
        for idx in xrange(nrows):
            offset = start+(idx*row_size)
            row = struct.unpack_from(row_fmt, data, offset)
            rows.append(row)
        return rows

