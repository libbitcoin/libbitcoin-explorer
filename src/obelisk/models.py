import bitcoin
import struct
import serialize

class BlockHeader:

    def __init__(self):
        self.height = None

    @classmethod
    def deserialize(cls, raw):
        assert len(raw) == 80
        self = cls()
        self.version = struct.unpack('<I', raw[:4])[0]
        self.previous_block_hash = raw[4:36][::-1]
        assert len(self.previous_block_hash) == 32
        self.merkle = raw[36:68][::-1]
        assert len(self.merkle) == 32
        self.timestamp, self.bits, self.nonce = struct.unpack('<III', raw[68:])
        return self

    @property
    def hash(self):
        data = struct.pack('<I', self.version)
        data += self.previous_block_hash[::-1]
        data += self.merkle[::-1]
        data += struct.pack('<III', self.timestamp, self.bits, self.nonce)
        return bitcoin.Hash(data)[::-1]

    def __repr__(self):
        return '<BlockHeader %s>' % (self.hash.encode("hex"),)

class OutPoint(object):
    def __init__(self):
        self.hash = None
        self.index = None

    def is_null(self):
        return (len(self.hash) == 0) and (self.index == 0xffffffff)

    def __repr__(self):
        return "OutPoint(hash=%s, index=%i)" % (self.hash.encode("hex"), self.index)

    def serialize(self):
        return serialize.ser_output_point(self)

    @staticmethod
    def deserialize(bytes):
        return serialize.deser_output_point(bytes)

class TxOut(object):
    def __init__(self):
        self.value = None
        self.script = ""

    def __repr__(self):
        return "TxOut(value=%i.%08i script=%s)" % (self.value // 100000000, self.value % 100000000, self.script.encode("hex"))

    def serialize(self):
        return serialize.ser_txout(self)

    @staticmethod
    def deserialize(bytes):
        return serialize.deser_txout(bytes)


class TxIn(object):
    def __init__(self):
        self.previous_output = OutPoint()
        self.script = ""
        self.sequence = 0xffffffff

    def is_final(self):
        return self.sequence == 0xffffffff

    def __repr__(self):
        return "TxIn(previous_output=%s script=%s sequence=%i)" % (repr(self.previous_output), self.script.encode("hex"), self.sequence)

    def serialize(self):
        return serialize.ser_txin(self)

    @staticmethod
    def deserialize(bytes):
        return serialize.deser_txin(bytes)

class Transaction:
    def __init__(self):
        self.version = 1
        self.locktime = 0
        self.inputs = []
        self.outputs = []

    def is_final(self):
        for tin in self.vin:
            if not tin.is_final():
                return False
        return True
    def is_coinbase(self):
        return len(self.vin) == 1 and self.vin[0].prevout.is_null()

    def __repr__(self):
        return "Transaction(version=%i inputs=%s outputs=%s locktime=%i)" % (self.version, repr(self.inputs), repr(self.outputs), self.locktime)

    def serialize(self):
        return serialize.ser_tx(self)

    @staticmethod
    def deserialize(bytes):
        return serialize.deser_tx(bytes)

