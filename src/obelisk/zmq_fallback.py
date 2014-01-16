import zmq
from twisted.internet import task
from twisted.internet import reactor

class ZmqSocket:

    context = zmq.Context(1)

    def __init__(self, cb, version):
        self._cb = cb

    def connect(self, address):
        self._socket = ZmqSocket.context.socket(zmq.DEALER)
        self._socket.connect(address)
        l = task.LoopingCall(self.poll)
        l.start(0.1)

    def poll(self):
        try:
            data = self._socket.recv(flags=zmq.NOBLOCK)
        except zmq.core.error.ZMQError:
            return
        more = self._socket.getsockopt(zmq.RCVMORE)
        self._cb(data, more)

    def send(self, data, more=0):
        if more:
            more = zmq.SNDMORE
        self._socket.send(data, more)

