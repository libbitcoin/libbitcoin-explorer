.. _tut-quickstart:

**********
Quickstart
**********

To see a list of the sx commands type:
::

    $ sx help
    Usage: sx COMMAND [ARGS]...

      -c, --config               Specify a config file

    The sx commands are:

    DETERMINISTIC KEYS AND ADDRESSES
       genaddr                    Generate a Bitcoin address deterministically from a wallet
                                  seed or master public key.
       genpriv                    Generate a private key deterministically from a seed.
       genpub                     Generate a public key deterministically from a wallet
                                  seed or master public key.
       mpk                        Extract a master public key from a deterministic wallet seed.
       newseed                    Create a new deterministic wallet seed.

    TRANSACTION PARSING
       showscript                 Show the details of a raw script.
       showtx                     Show the details of a transaction.

    BLOCKCHAIN QUERIES (blockexplorer.com)
       blke-fetch-transaction     Fetches a transaction from blockexplorer.com

    FORMAT
       base58-decode              Convert from base58 to hex
       base58-encode              Convert from hex to base58
       base58check-decode         Convert from base58check to hex
       base58check-encode         Convert from hex to base58check
       decode-addr                Decode an address to its internal RIPEMD representation.
       embed-addr                 Generate an address used for embedding record of data into the blockchain.
       encode-addr                Encode an address to base58check form.
       ripemd-hash                RIPEMD hash data from STDIN.
       unwrap                     Validates checksum and recovers version byte and original data from hexstring.
       validaddr                  Validate an address.
       wrap                       Adds version byte and checksum to hexstring.

    BRAINWALLET
       brainwallet                Make a private key from a brainwallet
       mnemonic                   Work with Electrum compatible mnemonics (12 words wallet seed).

    BLOCKCHAIN WATCHING
       monitor                    Monitor an address.
       watchtx                    Watch transactions from the network searching for a certain hash.

    BLOCKCHAIN QUERIES (blockchain.info)
       bci-fetch-last-height      Fetch the last block height using blockchain.info.
       bci-history                Get list of output points, values, and their spends
                                  from blockchain.info

    MISC
       btc                        Convert Satoshis into Bitcoins.
       initchain                  Initialize a new blockchain.
       qrcode                     Generate Bitcoin QR codes offline.
       satoshi                    Convert Bitcoins into Satoshis.
       showblkhead                Show the details of a block header.
       wallet                     Experimental command line wallet.

    MULTISIG ADDRESSES
       scripthash                 Create BIP 16 script hash address from raw script hex.

    LOOSE KEYS AND ADDRESSES
       addr                       See Bitcoin address of a public or private key.
       get-pubkey                 Get the pubkey of an address if available
       newkey                     Create a new private key.
       pubkey                     See the public part of a private key.

    STEALTH
       secret-to-wif              Convert a secret exponent value to Wallet. Import. Format.
       stealth-new                Generate a new master stealth secret.
       stealth-recv               Regenerate the secret from your master secret and provided nonce.
       stealth-send               Generate a new sending address and a stealth nonce.

    CREATE TRANSACTIONS
       mktx                       Create an unsigned tx.
       rawscript                  Create the raw hex representation from a script.
       set-input                  Set a transaction input.
       sign-input                 Sign a transaction input.

    VALIDATE
       validsig                   Validate a transaction input's signature.

    BLOCKCHAIN QUERIES
       balance                    Show balance of a Bitcoin address in satoshis.
       fetch-block-header         Fetch raw block header.
       fetch-last-height          Fetch the last block height.
       fetch-transaction          Fetch a raw transaction using a network connection to make requests against the obelisk load balancer backend.
       fetch-transaction-index    Fetch block height and index in block of transaction.
       get-utxo                   Get enough unspent transaction outputs from a given set of
                                  addresses to pay a given number of satoshis
       history                    Get list of output points, values, and their spends for an
                                  address. grep can filter for just unspent outputs which can
                                  be fed into mktx.
       validtx                    Validate a transaction.

    BLOCKCHAIN UPDATES
       sendtx-bci                 Send tx to blockchain.info/pushtx.
       sendtx-node                Send transaction to a single node.
       sendtx-obelisk             Send tx to obelisk server.
       sendtx-p2p                 Send tx to bitcoin network.

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

