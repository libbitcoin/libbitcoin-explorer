__author__ = 'bobalot'

import struct
import io
import hashlib
from binascii import hexlify, unhexlify
from hashlib import sha256
import models

from error_code import error_code, obelisk_exception

# Py3 compatibility
import sys
bchr = chr
if sys.version > '3':
    bchr = lambda x: bytes([x])


def deser_uint32(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    return struct.unpack(b"<I", f.read(4))[0]


def ser_uint32(u):
    rs = b""
    rs += struct.pack(b"<I", u & 0xFFFFFFFF)
    return rs


def deser_string(f):
    nit = struct.unpack(b"<B", f.read(1))[0]
    if nit == 253:
        nit = struct.unpack(b"<H", f.read(2))[0]
    elif nit == 254:
        nit = struct.unpack(b"<I", f.read(4))[0]
    elif nit == 255:
        nit = struct.unpack(b"<Q", f.read(8))[0]
    return f.read(nit)

def ser_string(s):
    if len(s) < 253:
        return bchr(len(s)) + s
    elif len(s) < 0x10000:
        return bchr(253) + struct.pack(b"<H", len(s)) + s
    elif len(s) < 0x100000000:
        return bchr(254) + struct.pack(b"<I", len(s)) + s
    return bchr(255) + struct.pack(b"<Q", len(s)) + s

def deser_hash(f):
    return f.read(32)

def ser_hash(h):
    return h[::-1]

def deser_uint256(f):
    r = 0
    for i in range(8):
        t = struct.unpack(b"<I", f.read(4))[0]
        r += t << (i * 32)
    return r

def ser_uint256(u):
    rs = b""
    for i in range(8):
        rs += struct.pack(b"<I", u & 0xFFFFFFFF)
        u >>= 32
    return rs

def ser_uint160(u):
    rs = b""
    for i in range(5):
        rs += struct.pack(b"<I", u & 0xFFFFFFFF)
        u >>= 32
    return rs

def uint160_from_str(s):
    r = 0
    t = struct.unpack(b"<IIIII", s[:20])
    for i in range(5):
        r += t[i] << (i * 32)
    return r

def uint256_from_str(s):
    r = 0
    t = struct.unpack(b"<IIIIIIII", s[:32])
    for i in range(8):
        r += t[i] << (i * 32)
    return r

def uint256_from_compact(c):
    nbytes = (c >> 24) & 0xFF
    v = (c & 0xFFFFFF) << (8 * (nbytes - 3))
    return v

def uint256_to_shortstr(u):
    s = "%064x" % (u,)
    return s[:16]

def deser_variable_uint(f):
    length = struct.unpack(b"<B", f.read(1))[0]
    if length < 0xfd:
        return length
    elif length == 0xfd:
        return struct.unpack(b"<H", f.read(2))[0]
    elif length == 0xfe:
        return struct.unpack(b"<I", f.read(4))[0]
    return struct.unpack(b"<Q", f.read(8))[0]

def deser_vector(f, c, arg1=None):
    count = deser_variable_uint(f)
    r = []
    for i in range(count):
        #if arg1 is not None:
        #    t = c(arg1)
        #else:
        #    t = c()

        if c is models.TxIn:
            t = deser_txin(f)
        elif c is models.TxOut:
            t = deser_txout(f)
        elif c is models.Transaction:
            t = deser_tx(f)
        else:
            raise NotImplementedError

        r.append(t)
    return r

def ser_vector(l):
    r = b""
    if len(l) < 253:
        r = bchr(len(l))
    elif len(l) < 0x10000:
        r = bchr(253) + struct.pack(b"<H", len(l))
    elif len(l) < 0x100000000:
        r = bchr(254) + struct.pack(b"<I", len(l))
    else:
        r = bchr(255) + struct.pack(b"<Q", len(l))
    for i in l:

        if type(i) is models.TxIn:
            r += ser_txin(i)
        elif type(i) is models.TxOut:
            r += ser_txout(i)
        elif type(i) is models.Transaction:
            r += ser_tx(i)
        else:
            raise NotImplementedError

    return r

def deser_uint256_vector(f):
    nit = struct.unpack(b"<B", f.read(1))[0]
    if nit == 253:
        nit = struct.unpack(b"<H", f.read(2))[0]
    elif nit == 254:
        nit = struct.unpack(b"<I", f.read(4))[0]
    elif nit == 255:
        nit = struct.unpack(b"<Q", f.read(8))[0]
    r = []
    for i in range(nit):
        t = deser_uint256(f)
        r.append(t)
    return r

def ser_uint256_vector(l):
    r = b""
    if len(l) < 253:
        r = bchr(len(l))
    elif len(s) < 0x10000:
        r = bchr(253) + struct.pack(b"<H", len(l))
    elif len(s) < 0x100000000:
        r = bchr(254) + struct.pack(b"<I", len(l))
    else:
        r = bchr(255) + struct.pack(b"<Q", len(l))
    for i in l:
        r += ser_uint256(i)
    return r

def deser_string_vector(f):
    nit = struct.unpack(b"<B", f.read(1))[0]
    if nit == 253:
        nit = struct.unpack(b"<H", f.read(2))[0]
    elif nit == 254:
        nit = struct.unpack(b"<I", f.read(4))[0]
    elif nit == 255:
        nit = struct.unpack(b"<Q", f.read(8))[0]
    r = []
    for i in range(nit):
        t = deser_string(f)
        r.append(t)
    return r

def ser_string_vector(l):
    r = b""
    if len(l) < 253:
        r = bchr(len(l))
    elif len(s) < 0x10000:
        r = bchr(253) + struct.pack(b"<H", len(l))
    elif len(s) < 0x100000000:
        r = bchr(254) + struct.pack(b"<I", len(l))
    else:
        r = bchr(255) + struct.pack(b"<Q", len(l))
    for sv in l:
        r += ser_string(sv)
    return r

def deser_int_vector(f):
    nit = struct.unpack(b"<B", f.read(1))[0]
    if nit == 253:
        nit = struct.unpack(b"<H", f.read(2))[0]
    elif nit == 254:
        nit = struct.unpack(b"<I", f.read(4))[0]
    elif nit == 255:
        nit = struct.unpack(b"<Q", f.read(8))[0]
    r = []
    for i in range(nit):
        t = struct.unpack(b"<i", f.read(4))[0]
        r.append(t)
    return r

def ser_int_vector(l):
    r = b""
    if len(l) < 253:
        r = bchr(len(l))
    elif len(s) < 0x10000:
        r = bchr(253) + struct.pack(b"<H", len(l))
    elif len(s) < 0x100000000:
        r = bchr(254) + struct.pack(b"<I", len(l))
    else:
        r = bchr(255) + struct.pack(b"<Q", len(l))
    for i in l:
        r += struct.pack(b"<i", i)
    return r

def Hash(s):
    return uint256_from_str(hashlib.sha256(hashlib.sha256(s).digest()).digest())

def Hash160(s):
    h = hashlib.new('ripemd160')
    h.update(hashlib.sha256(s).digest())
    return uint160_from_str(h.digest())


def ser_destination(destination):
    if destination is None:
        serialized = ""
    else:
        try:
            serialized = unhexlify(destination)
        except TypeError:
            serialized = destination

    return serialized

def deser_txout(f):
    txout = models.TxOut()
    txout.value = struct.unpack(b"<q", f.read(8))[0]
    txout.script = deser_string(f)
    return txout

def ser_txout(txout):
    r = b""
    r += struct.pack(b"<q", txout.value)
    r += ser_string(txout.script)
    return r


def deser_output_point(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    outpoint = models.OutPoint()
    outpoint.hash = deser_hash(f)
    outpoint.index = deser_uint32(f.read(4))
    return outpoint


def ser_output_point(outpoint):
    r = b""
    r += ser_hash(outpoint.hash)
    r += ser_uint32(outpoint.index)
    return r


def deser_txin(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    txin = models.TxIn()
    txin.previous_output = deser_output_point(f)
    txin.script = deser_string(f)
    txin.sequence = deser_uint32(f)
    return txin

def ser_txin(txin):
    r = b""
    r += ser_output_point(txin.previous_output)
    r += ser_string(txin.script)
    r += ser_uint32(txin.sequence)
    return r


def deser_block_header(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    h = models.BlockHeader()

    h.version = deser_uint32(f.read(4))
    h.previous_block_hash = f.read(32)
    h.merkle = f.read(32)
    h.timestamp = deser_uint32(f.read(4))
    h.bits = deser_uint32(f.read(4))
    h.nonce = deser_uint32(f.read(4))

    return h


def ser_block_header(block_header):
    output = b""
    output += ser_uint32(block_header.version)
    output += block_header.previous_block_hash
    output += block_header.merkle
    output += ser_uint32(block_header.timestamp)
    output += ser_uint32(block_header.bits)
    output += ser_uint32(block_header.nonce)

    return output


def deser_tx(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    tx = models.Transaction()
    tx.version = deser_uint32(f.read(4))
    tx.inputs = deser_vector(f, models.TxIn)
    tx.outputs = deser_vector(f, models.TxOut)
    tx.locktime = deser_uint32(f)
    return tx


def ser_tx(tx):
    r = b""
    r += ser_uint32(tx.version)
    r += ser_vector(tx.inputs)
    r += ser_vector(tx.outputs)
    r += ser_uint32(tx.locktime)
    return r


def deser_block(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    blk = models.Block()

    blk.header = deser_block_header(f)
    blk.transactions = deser_vector(f, models.Transaction)
    return Block

def ser_block(blk):
    r = b""
    r += ser_block_header(blk.header)
    r += ser_vector(blk.transaction_list, models.Transaction)

    return r


    #tx.version = struct.unpack(b"<i", f.read(4))[0]
    #tx.vin = deser_vector(f, TxIn)
    #tx.vout = deser_vector(f, TxOut)
    #tx.nLockTime = struct.unpack(b"<I", f.read(4))[0]


def deser_history_row(f):

    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    hr = models.history_row()


    hr.output_hash = f.read(32)
    hr.output_index = deser_uint32(f)
    hr.output_height = deser_uint32(f)

    hr.value = struct.unpack(b"<q", f.read(8))[0]
    hr.spend_hash = f.read(32)
    hr.spend_index = deser_uint32(f)
    hr.spend_height = deser_uint32(f)

    return hr

def ser_history_row(hr):
    r = b""

    r += hr.output_hash
    r += ser_uint32(hr.output_index)
    r += ser_uint32(hr.output_height)

    r += struct.pack(b"<q", hr.value & 0xFFFFFFFFFFFFFFFF)
    r += hr.spend_hash
    r += ser_uint32(hr.spend_index)
    r += ser_uint32(hr.spend_height)

    return hr


def deser_history_row_list(bytes):
    row_bytes = 88
    num_rows = len(bytes)/88

    assert(len(bytes) % 88 == 0)

    history_list = []

    for i in range(num_rows):
        history_list.append(deser_history_row(bytes[i*88, i*88+88]))

    return history_list


def dsha256(data):
    return sha256(sha256(data).digest()).digest()[::-1]


def checksum(data):
    return sha256(sha256(data).digest()).digest()[:4]


def hash_block_header(blk_head):
    if type(blk_head) is models.Block:
        blk_head = blk_head.header

    serial = ser_block_header(blk_head)

    return dsha256(serial)


def hash_transaction(tx):
    if type(tx) is not models.Transaction:
        return False

    serial = ser_tx(tx)

    return dsha256(serial)


def ser_data(command, data):
    # This requires command at the moment, for no reason.
    # Fix this.
    #from models import commands
    #if command not in commands:
    #    raise NotImplementedError

    if type(data) is int:
        return ser_uint32(data)
    elif type(data) is str:
        return data

    elif type(data) is tuple:
        r = b""

        for element in data:

            r += ser_data(command, element)

        return r

def deser_address_update(f):
    if type(f) is not io.BytesIO:
        f = io.BytesIO(f)

    update = models.address_update()
    update.address_version_byte = f.read(1)
    update.address_hash = f.read(20)

    update.height = deser_uint32(f)
    update.tx = deser_tx(f)

    return update


#command_data_type = \
#        {"blockchain.fetch_transaction",
#            "blockchain.fetch_last_height",
#            "blockchain.fetch_block_header",
#            "blockchain.fetch_block_transaction_hashes",
#            "transaction_pool.validate",
#            "protocol.broadcast_transaction",
#            "address.fetch_history"]


# deserialize and remove the ec here, this leaves all the other functions able to
# do deserialization on normal bitcoin serials.
def deser_data(command, data_bytes):
    if command == "blockchain.fetch_transaction":
        return data_bytes[:4], deser_tx(data_bytes[4:])

    elif command == "blockchain.fetch_last_height":
        return data_bytes[:4], deser_uint32(data_bytes[4:])

    elif command == "blockchain.fetch_block_header":
        return data_bytes[:4], deser_block_header(data_bytes[4:])

    elif command == "blockchain.fetch_block_transaction_hashes":
        hash_list = []

        print hexlify(data_bytes[4:])

        assert((len(data_bytes)-4) % 32 == 0)

        f = io.BytesIO(data_bytes)
        ec = f.read(4)

        for i in range(data_bytes/32):
            hash_list.append(f.read(32))

        return ec, hash_list

    elif command == "address.fetch_history":
        # history row is 88 bytes long. Assert there is nothing else
        assert((len(data_bytes)-4) % 88 == 0)

        history_list = []

        # use bytesio, as this will probably be a long message
        f = io.BytesIO(data_bytes)
        ec = f.read(4)

        for i in range(len(data_bytes) / 88):
            history_list.append(deser_history_row(f))

        return ec, history_list

    elif command == "address.subscribe":
        if len(data_bytes) == 4:
            ec = deser_uint32(data_bytes)

        return ec, None

    elif command == "address.update":
        # No error code in address.update
        f = io.BytesIO(data_bytes)

        ec = 0
        return ec, deser_address_update(f)







