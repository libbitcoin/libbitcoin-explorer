class ChainParameters(object):
    def __init__(self, magic_bytes, pubkey_version, script_version, wif_version, protocol_port):
        self.magic_bytes = magic_bytes
        self.pubkey_version = pubkey_version
        self.script_version = script_version
        self.wif_version = wif_version
        self.protocol_port = protocol_port

testnet_chain = ChainParameters(0x0709110b, 0x6F, 0xC4, 0xEF, 18333)
mainnet_chain = ChainParameters(0xd9b4bef9, 0x00, 0x05, 0x80, 8333)

ENABLE_TESTNET = False

if ENABLE_TESTNET:
    chain = testnet_chain
else:
    chain = mainnet_chain
