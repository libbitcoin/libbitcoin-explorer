#!/usr/bin/python
import sys
import subprocess

SPACING = " " * 30

command_list = {

"satoshi": (
"MISC",
"Convert Bitcoins into Satoshis.",

"""\
Usage: sx satoshi BTC
Convert Bitcoins into Satoshis.\
"""
),

"btc": (
"MISC",
"Convert Satoshis into Bitcoins.",

"""\
Usage: sx btc SATOSHIS
Convert Satoshis into Bitcoins.\
"""
),

"showscript": (
"BLOCKCHAIN QUERIES",
"Show the details of a raw script.",

"""\
Usage: sx showscript
Show the details of a raw script.\
"""
),

"scripthash": (
"UNSIGNED TRANSACTIONS",
"Create BIP 16 script hash address from raw script hex.",

"""\
Usage: sx scripthash
Create BIP 16 script hash address from raw script hex (from STDIN).\
"""
),

"rawscript": (
"UNSIGNED TRANSACTIONS",
"Create the raw hex representation from a script.",

"""\
Usage: sx rawscript [ARGS]...
Create the raw hex representation from a script.\
"""
),

"initchain": (
"MISC",
"Initialize a new blockchain.",

"""\
Usage: sx initchain DIRECTORY
Initialize a new blockchain.\
"""
),

"wallet": (
"MISC",
"Experimental command line wallet.",

"""\
Usage: sx wallet SEED
This is an experimental prototype.\
"""
),

"monitor": (
"BLOCKCHAIN WATCHING",
"Monitor an address.",

"""\
Usage: sx monitor ADDRESS
Monitor an address.\
"""
),

"validaddr": (
"FORMAT",
"Validate an address.",

"""\
Usage: sx validaddr ADDRESS
Validate an address.\
"""
),

"validtx": (
"VALIDATE",
"Validate a transaction.",

"""\
Usage: sx validtx FILENAME
Validate a transaction.\
"""
),

"pubkey": (
"LOOSE KEYS AND ADDRESSES",
"See the public part of a private key.",

"""\
Usage: sx pubkey
Read private key from STDIN and output the public key.\
"""
),

"addr": (
"LOOSE KEYS AND ADDRESSES",
"See Bitcoin address of a private key.",

"""\
Usage: sx addr
Read private key from STDIN and output Bitcoin address.\
"""
),

"ripemd-hash": (
"FORMAT",
"RIPEMD hash data from STDIN.",

"""\
Usage: sx ripemd-hash
RIPEMD hash data from STDIN.\
"""
),

"wrap": (
"FORMAT",
"Adds version byte and checksum to hexstring.",

"""\
Usage: sx wrap HEXSTRING VERSION_BYTE <or> echo HEXSTRING | sx wrap VERSION_BYTE
Adds version byte and checksum to hexstring.\
"""
),

"unwrap": (
"FORMAT",
"Validates checksum and recovers version byte and original data from hexstring.",

"""\
Usage: sx wrap HEXSTRING VERSION_BYTE <or> echo HEXSTRING | sx wrap VERSION_BYTE
Validates checksum and recovers version byte and original data from hexstring.\
"""
),

"base58-decode": (
"FORMAT",
"Convert from base58 to hex",

"""\
Usage: sx base58-decode B58STRING <or> echo B58STRING | sx base58-decode
Convert from base58 to hex.\
"""
),

"base58-encode": (
"FORMAT",
"Convert from hex to base58",

"""\
Usage: sx base58-encode HEXSTRING <or> echo HEXSTRING | sx base58-encode
Convert from hex to base58.\
"""
),

"base58check-decode": (
"FORMAT",
"Convert from base58check to hex",

"""\
Usage: sx base58check-decode B58STRING <or> echo B58STRING | sx base58check-decode
Convert from base58check to hex.\
"""
),

"base58check-encode": (
"FORMAT",
"Convert from hex to base58check",

"""\
Usage: sx base58check-encode HEXSTRING <or> echo HEXSTRING | sx base58check-encode
Convert from hex to base58check.\
"""
),

"ob-broadcast-tx": (
"BLOCKCHAIN UPDATES",
"Broadcast tx to obelisk server.",

"""\
Usage: sx ob-broadcast-tx FILENAME
Broadcast the transaction to an obelisk server for the network.

  $ sx ob-broadcast-tx txfile.tx
\
"""
),

"broadcast-tx": (
"BLOCKCHAIN UPDATES",
"Broadcast tx to network.",

"""\
Usage: sx broadcast-tx FILENAME
Broadcast the transaction to the Bitcoin network.

  $ sx broadcast-tx txfile.tx
\
"""
),

"bci-pushtx": (
"BLOCKCHAIN UPDATES",
"Push tx to blockchain.info/pushtx.",

"""\
Usage: sx bci-push-tx FILENAME
Push tx to blockchain.info/pushtx.

  $ sx bci-pushtx txfile.tx
\
"""
),

"blke-fetch-transaction": (
"BLOCKCHAIN UPDATES",
"Fetches a transaction from blockexplorer.com",

"""\
Usage: sx blke-fetch-transaction HASH

Fetches a transaction from blockexplorer.com

  $ sx blke-fetch-transaction HASH
\
"""
),

"genpriv": (
"DETERMINISTIC KEYS AND ADDRESSES",
"Generate a private key deterministically from a seed.",

"""\
Usage: sx genpriv N [CHANGE]
Generate private keys from a wallet seed.

  $ cat wallet.seed | sx genpriv 0
  5Jmb4EYzEqj63rkPwADFY7WyGV2kga3YB1HfDAzg9dHNG57NMPu
  $ cat wallet.seed | sx genpriv 1
  5KjCYpPyxU2e88S57b1naKUsJ1JNjCudkFSQPxqcYyBYgzzahNe
\
"""
),

"genpub": (
"DETERMINISTIC KEYS AND ADDRESSES",
"Generate a public key deterministically from a wallet\n" +
SPACING + "seed or master public key.",

"""\
Usage: sx genpub N [CHANGE]
Generate public key from a wallet seed or master public key.

  $ cat wallet.seed | sx genpub 0
  040a053d0a42d58b7e34346daae9d40ce33fad5d65bbaa6c615a2b76447734b2c712b5d45de839b2e5e7ac00201cbea3d2d376cfcc7a3f3f508f1e6761f6c271bf
\
"""
),

"genaddr": (
"DETERMINISTIC KEYS AND ADDRESSES",
"Generate a Bitcoin address deterministically from a wallet\n" +
SPACING + "seed or master public key.",

"""\
Usage: sx genaddr N [CHANGE]
Generate Bitcoin addresses from a wallet seed or master public key.

  $ cat wallet.seed | sx genaddr 0
  1a4b47AC4ydSnAAcTNH1qozHq2pwJb644
\
"""
),

"qrcode": (
"MISC",
"Generate Bitcoin QR codes offline.",

"""\
Usage: sx qrcode

Make sure you have the program 'qrencode' installed first.

  $ sudo apt-get install qrencode
  $ sx qrcode 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe qrcode.png
\
"""
),

"fetch-block-header": (
"BLOCKCHAIN QUERIES",
"Fetch raw block header.",

"""\
Usage: sx fetch-block-header [HASH] [HEIGHT]

The fetch-block-header tool uses a network connection to make requests against
the load balancer backend.\
"""
),

"fetch-last-height": (
"BLOCKCHAIN QUERIES",
"Fetch the last block height.",

"""\
Usage: sx fetch-last-height

The fetch-last-height tool uses a network connection to make requests against
the load balancer backend.\
"""
),

"bci-fetch-last-height": (
"BLOCKCHAIN QUERIES",
"Fetch the last block height using blockchain.info.",

"""\
Usage: sx bci-fetch-last-height

Fetch the last block height using blockchain.info.\
"""
),

"fetch-transaction": (
"BLOCKCHAIN QUERIES",
"Fetch a raw transaction.",

"""\
Usage: sx fetch-transaction HASH

The fetch-transaction tool uses a network connection to make requests against
the load balancer backend.\
"""
),

"fetch-transaction-index": (
"BLOCKCHAIN QUERIES",
"Fetch block height and index in block of transaction.",

"""\
Usage: sx fetch-transaction-index HASH

The fetch-transaction-index tool uses a network connection to make requests
against the load balancer backend.\
"""
),

"balance": (
"BLOCKCHAIN QUERIES",
"Show balance of a Bitcoin address.",

"""\
Usage: sx balance ADDRESS

The balance tool uses a network connection to make requests against the
load balancer backend.

  $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx balance
  100000
\
"""
),

"history": (
"BLOCKCHAIN QUERIES",
"Get list of output points, values, and their spends for an\n" +
SPACING + "address. grep can filter for just unspent outputs which can\n" +
SPACING + "be fed into mktx.",

"""\
Usage: sx history ADDRESS

The history tool uses a network connection to make requests against the
load balancer backend.

  -j, --json                 Enable json parseable output.

Example:

  $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx history
  Output Hash:Index                           Output Height   Value (Satoshis) Spend Hash:Index                Spend Height
  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1  247683 100000      Unspent                                 230529504
\
"""
),

"bci-history": (
"BLOCKCHAIN QUERIES",
"Get list of output points, values, and their spends\n" +
SPACING + "from blockchain.info",

"""\
Usage: sx bci-history SATOSHIS
Get list of output points, values and spends using blockchain.info.\
"""
),

"get-utxo": (
"BLOCKCHAIN QUERIES",
"Get enough unspent transaction outputs from a given set of\n" +
SPACING + "addresses to pay a given number of satoshis",

"""\
Usage: sx get-utxo ADDRESS1 ADDRESS2... SATOSHIS
Get enough unspent transaction outputs from a given set of addresses to pay a given number of satoshis\
"""
),

"get-pubkey": (
"LOOSE KEYS AND ADDRESSES",
"Get the pubkey of an address if available",

"""\
Usage: sx get-pubkey ADDRESS
Get the pubkey of an address if available\
"""
),

"mktx": (
"UNSIGNED TRANSACTIONS",
"Create an unsigned tx.",

"""\
        Usage: sx mktx FILENAME [-i TXHASH:INDEX]... [-o ADDRESS:VALUE] [-o HEXSCRIPT:VALUE]

  -i, --input TXHASH:INDEX      Add input to transaction.
  -o, --output ADDRESS:VALUE or HEXSCRIPT:VALUE
                                Add output to transaction.

Construct the transaction:

  $ sx mktx txfile.tx -i 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1 -o 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000

The VALUE field is in Satoshis.\
"""
),

"mpk": (
"DETERMINISTIC KEYS AND ADDRESSES",
"Extract a master public key from a deterministic wallet seed.",

"""\
Usage: sx mpk

Extract a master public key from a deterministic wallet seed.

  $ sx newseed > wallet.seed
  $ cat wallet.seed
  b220b5bd2909df1d74b71c9e664233bf
  $ cat wallet.seed | sx mpk > master_public.key
\
"""
),

"newkey": (
"LOOSE KEYS AND ADDRESSES",
"Create a new private key.",

"""\
Usage: sx newkey

  $ sx newkey
  5KPFsatiYrJcvCSRrDbtx61822vZjeGGGx3wu38pQDHRF8eVJ8H
\
"""
),

"newseed": (
"DETERMINISTIC KEYS AND ADDRESSES",
"Create a new deterministic wallet seed.",

"""\
Usage: sx newseed

  $ sx newseed
  b220b5bd2909df1d74b71c9e664233bf
\
"""
),

"sendtx": (
"BLOCKCHAIN UPDATES",
"Send transaction to a single node.",

"""\
Usage: sx sendtx FILENAME [HOST] [PORT]

HOST and PORT default to localhost:8333.

Send transaction to one Bitcoin node on localhost port 4009:

  $ sx sendtx txfile.tx localhost 4009
\
"""
),

"showblkhead": (
"BLOCKCHAIN QUERIES",
"Show the details of a block header.",

"""\
Usage: sx showblkhead FILENAME

'showblkhead' allows inspecting of block headers.

  $ sx showblkhead headerfile.blk
  hash: 4d25b18ed094ad68f75f21692d8540f45ceb90b240a521b8f191e95d8b6b8bb0
  version: 1  locktime: 0
  Input:
    previous output:
  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0
    script:   sequence: 4294967295
  Output:
    value: 90000
    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify
  checksig
    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe
\
"""
),

"showtx": (
"BLOCKCHAIN QUERIES",
"Show the details of a transaction.",

"""\
Usage: sx showtx [-j] FILENAME

'showtx' allows inspecting of tx files.

  -j, --json                 Enable json parseable output.

Example:

  $ sx showtx txfile.tx
  hash: 4d25b18ed094ad68f75f21692d8540f45ceb90b240a521b8f191e95d8b6b8bb0
  version: 1  locktime: 0
  Input:
    previous output:
  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0
    script:   sequence: 4294967295
  Output:
    value: 90000
    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify
  checksig
    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe
\
"""
),

"decode-addr": (
"FORMAT",
"Decode an address to its internal RIPEMD representation.",

"""\
Usage: sx decode-addr ADDRESS
Decode an address to its internal RIPEMD representation.\
"""),

"embed-addr": (
"FORMAT",
"Generate an address used for embedding record of data into the blockchain.",

"""\
Usage: sx embed-addr
Generate an address used for embedding record of data into the blockchain.

Example:

  $ cat my_sculpture.jpg | sx embed-addr
  1N9v8AKBqst9MNceV3gLmFKsgkKv1bZcBU

Now send some Bitcoin to that address and it'll be embedded in the blockchain
as a record of the data passed in.
\
"""),

"encode-addr": (
"FORMAT",
"Encode an address to base58check form.",

"""\
Usage: sx encode-addr HASH [VERSION]
Encode an address to base58check form.\
"""),

"validsig": (
"VALIDATE",
"Validate a transaction input's signature.",

"""\
Usage: sx validsig FILENAME INDEX SCRIPT_CODE SIGNATURE
Validate a transaction input's signature.\
"""),

"brainwallet": (
"BRAINWALLET",
"Make a private key from a brainwallet",

"""\
Usage: sx brainwallet password
       sx brainwallet username password
       sx brainwallet password --algo slowsha
       sx brainwallet username password --algo slowsha
Make a private key from a brainwallet.\
"""
),

"set-input": (
"UNSIGNED TRANSACTIONS",
"Set a transaction input.",

"""\
Usage: sx sign-input FILENAME INDEX PREVOUT_SCRIPT
Set a transaction input.\
"""),

"sign-input": (
"SIGNED TRANSACTIONS",
"Sign a transaction input.",

"""\
Usage: sx sign-input FILENAME INDEX

Sign a transaction input.

Note how the input script in the following transaction is empty.

  $ sx showtx txfile.tx
  hash: 4d25b18ed094ad68f75f21692d8540f45ceb90b240a521b8f191e95d8b6b8bb0
  version: 1  locktime: 0
  Input:
    previous output:
  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0
    script:   sequence: 4294967295
  Output:
    value: 90000
    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify
  checksig
    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe

We will now sign the first input using our private key.

  $ cat private.key | sx sign-input txfile.tx 0
  $ sx showtx txfile.tx
  hash: 4a8be467fb75f0f757649348dbb05762142236ec236ac9e55e4683d7083ffca2
  version: 1  locktime: 0
  Input:
    previous output:
  97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:0
    script: [
  304602210083f8b5131f6399cdc01ed8368f6137f288f771e40834a94d65cee6b380fec873022100da5ed6d1d283f228752a88c2d6f629587b2a6fbc102202ae7c20f48af7c0533c01
  ] [
  04e3af7cdfaab6ba2f14001a7ea0a490f40c6ba43607be92a05111d2e8fc1eecf6fa2c248b3e25ddf7db081684f6f49dc83fd7b9b5a3a88a2e6b83b918f8972351
  ]  sequence: 4294967295
    address: 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz
  Output:
    value: 90000
    script: dup hash160 [ 18c0bd8d1818f1bf99cb1df2269c645318ef7b73 ] equalverify
  checksig
    address: 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe

Now the input script is prepared, and the transaction is signed.\
"""
),

"mnemonic": (
"BRAINWALLET",
"Work with Electrum compatible mnemonics (12 words wallet seed).",

"""\
Usage: sx mnemonic

Electrum compatible 12 word seeds.

  $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic
  people blonde admit dart couple different truth common alas stumble time cookie
  $ echo "people blonde admit dart couple different truth common alas
stumble time cookie" | sx mnemonic
  148f0a1d77e20dbaee3ff920ca40240d
\
"""
),

"watchtx": (
"BLOCKCHAIN WATCHING",
"Watch transactions from the network searching for a certain hash.",

"""\
Usage: sx watchtx [TXHASH]...

Watch transactions from the network searching for a certain hash.\
"""
),

}

def display_usage():
    print "Usage: sx COMMAND [ARGS]..."
    print
    print "The most commonly used sx commands are:"
    print
    categorised = {}
    for cmd in sorted(command_list.iterkeys()):
        category = command_list[cmd][0]
        if category not in categorised:
            categorised[category] = []
        short_desc = command_list[cmd][1]
        line = "   %s" % cmd
        line += " " * (len(SPACING) - len(cmd) - 3)
        line += short_desc
        categorised[category].append(line)
    for category, lines in categorised.iteritems():
        print category
        for line in lines:
            print line
        print
    print "See 'sx help COMMAND' for more information on a specific command."
    print
    print "SpesmiloXchange home page: <http://sx.dyne.org/>"

def display_help(command):
    assert command in command_list
    long_desc = command_list[command][2]
    print long_desc
    return 0

def display_bad(command):
    print "sx: '%s' is not a sx command. See 'sx --help'." % command
    return 1

def main(argv):
    if len(argv) == 1:
        display_usage()
        return 1
    command = argv[1]
    # args as one string we can pass to the sx sub-command
    args = argv[2:]
    if command == "help" or command == "--help" or command == "-h":
        if not args:
            display_usage()
            return 0
        return display_help(args[0])
    elif command in command_list:
        # make will come and substitute @corebindir@
        binary = "@corebindir@/sx-%s" % command
        return subprocess.call([binary] + args)
    else:
        return display_bad(command)
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv))

