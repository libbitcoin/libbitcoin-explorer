.. _tut-quickstart:

**********
Quickstart
**********

To see a list of the sx commands type:
::

    $ sx help
    Usage: sx COMMAND [ARGS]...
    
    The most commonly used sx commands are:
    
       addr                See Bitcoin address of a private key.
       balance             Show balance of a Bitcoin address.
       broadcast-tx        Broadcast tx to network.
       btc                 Convert Satoshis into Bitcoins.
       decode-addr         Decode an address to its internal RIPEMD representation.
       fetch-block-header  Fetch raw block header.
       fetch-last-height   Fetch the last block height.
       fetch-transaction   Fetch a raw transaction.
       genaddr             Generate a Bitcoin address deterministically from a wallet
                           seed or master public key.
       genpriv             Generate a private key deterministically from a seed.
       genpub              Generate a public key deterministically from a wallet
                           seed or master public key.
       history             Get list of output points, values, and their spends for an
                           address. grep can filter for just unspent outputs which can
                           be fed into mktx.
       mktx                Create an unsigned tx.
       mnemonic            Work with Electrum compatible mnemonics (12 words wallet seed).
       mpk                 Extract a master public key from a deterministic wallet seed.
       newkey              Create a new private key.
       newseed             Create a new deterministic wallet seed.
       pubkey              See the public part of a private key.
       qrcode              Generate Bitcoin QR codes offline.
       rawscript           Create the raw hex representation from a script.
       satoshi             Convert Bitcoins into Satoshis.
       scripthash          Create BIP 16 script hash address from raw script hex.
       sendtx              Send transaction to a single node.
       set-input           Set a transaction input.
       showblkhead         Show the details of a block header.
       showscript          Show the details of a raw script.
       showtx              Show the details of a transaction.
       sign-input          Sign a transaction input.
       watchtx             Watch transactions from the network searching for a certain hash.
    
    See 'sx help COMMAND' for more information on a specific command.
    
    SpesmiloXchange home page: <http://sx.dyne.org/>

All output for amounts are designated in Satoshis.
::

    $ sx balance 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY
    Paid balance:    9000
    Pending balance: 90000
    Total received:  239659000

To convert between Satoshis and BTC, use the `satoshi` and `btc` commands
respectively.
::

    $ sx btc 90000
    0.00090000
    $ sx satoshi 0.00090000
    90000

