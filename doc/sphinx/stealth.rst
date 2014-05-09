.. _tut-stealth:

****************
Stealth Payments
****************

Stealth payments is an anonymity technique that protects the privacy of
the recipient. The concept was invented by BitcoinByte and Peter Todd, and
is powerful tool for allowing one to accept Bitcoins using a public Bitcoin
address while preventing passive observers from knowing your transaction
history.

SX provides commands for working with stealth transactions, and for
understanding the mechanics behind them.
::

    $ sx help

    ...

    STEALTH
       stealth-addr               See a stealth address from given input.
       stealth-initiate           Initiate a new stealth payment.
       stealth-newkey             Generate new stealth keys and an address.
       stealth-show-addr          Show details for a stealth address.
       stealth-uncover            Uncover a stealth address.
       stealth-uncover-secret     Uncover a stealth secret.

    ...

    EC MATH
       ec-multiply                Multiply an integer and a point together.
       ec-tweak-add               Calculate the result of POINT + INTEGER * G.
    
    ...
    
    BLOCKCHAIN QUERIES
       fetch-stealth              Fetch a stealth information using a network connection
                                  to make requests against the obelisk load balancer backend.

Creating a stealth tx and discovering the secret
------------------------------------------------
    
Alice creates a new stealth address.
::

    $ sx stealth-newkey
    Stealth address: vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L
    Scan secret: af4afaeb40810e5f8abdbb177c31a2d310913f91cf556f5350bca10cbfe8b9ec
    Spend secret: d39758028e201e8edf6d6eec6910ae4038f9b1db3f2d4e2d109ed833be94a026
    $ SCAN_SECRET=af4afaeb40810e5f8abdbb177c31a2d310913f91cf556f5350bca10cbfe8b9ec
    $ SPEND_SECRET=d39758028e201e8edf6d6eec6910ae4038f9b1db3f2d4e2d109ed833be94a026

Alice can then post her stealth address (vJmwY32e...) publically on an internet
forum or her website, and nobody except Alice can see the history for that address.
Despite every Bitcoin transaction being public, transactions paying to Alice
have no public connection to her stealth address through the power of crypto.

Bob now takes Alice's stealth address and sends her 100 Satoshis. His wallet
creates a new address using stealth and adds extra metadata to the
transaction.
::

    $ sx mktx txfile.tx --output vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L:100
    Added output sending 100 Satoshis to 1BjqrpQqr4tY5YPQkL8aG7NGkFbTbiuVu.
    $ cat txfile.tx | sx showtx
    hash: 40926721556f9f923aa8d5c1ad2b2529462b43fd5cbd788e4cf21c408be2d6d0
    version: 1
    locktime: 0
    Output:
      value: 0
      script: return [ 060000000003b8a715c9432b2b52af9d58aaaf0ccbdefe36d45e158589ecc21ba2f064ebb315 ]
      stealth ephemkey: 03b8a715c9432b2b52af9d58aaaf0ccbdefe36d45e158589ecc21ba2f064ebb315
      stealth bitfield: 2696751161
    Output:
      value: 100
      script: dup hash160 [ 0207ec32af47c7af2321793569ec74182c114d62 ] equalverify checksig
      address: 1BjqrpQqr4tY5YPQkL8aG7NGkFbTbiuVu

The transaction is then sent publically to the network becoming part of the
blockchain, whereby Alice is able to detect and decode the data.
In the output above, there are 2 outputs with the first containing the stealth
metadata and the second containing the actual payment. Transactions can have
multiple stealth payments but the metadata and payment always occurs in pairs.
::

    stealth ephemkey: 03b8a715c9432b2b52af9d58aaaf0ccbdefe36d45e158589ecc21ba2f064ebb315
    address: 1BjqrpQqr4tY5YPQkL8aG7NGkFbTbiuVu

Alice can use the ephemkey and her stealth address to generate an address.
If the address matches that in the transaction, then Alice knows that this
payment is hers.
::

    $ sx stealth-uncover 
    Usage: sx stealth-uncover EPHEM_PUBKEY SCAN_SECRET SPEND_PUBKEY
    $ EPHEM_PUBKEY=03b8a715c9432b2b52af9d58aaaf0ccbdefe36d45e158589ecc21ba2f064ebb315
    $ SPEND_PUBKEY=$(echo $SPEND_SECRET | sx pubkey)
    $ sx stealth-uncover $EPHEM_PUBKEY $SCAN_SECRET $SPEND_PUBKEY 
    023fb525d59f08de4e25a3c589dffbf31ff0786b2312d7ff9efcebbd00185c55e5
    $ sx stealth-uncover $EPHEM_PUBKEY $SCAN_SECRET $SPEND_PUBKEY | sx addr
    1BjqrpQqr4tY5YPQkL8aG7NGkFbTbiuVu

Because the final adresses match, we know this payment is ours. We can create
the secret key using:
::

    $ sx stealth-uncover-secret
    Usage: sx stealth-uncover-secret EPHEM_PUBKEY SCAN_SECRET SPEND_SECRET
    $ sx stealth-uncover-secret $EPHEM_PUBKEY $SCAN_SECRET $SPEND_SECRET 
    6134396c3bc9a56ccaf80cd38728e6d3a7751524246e7924b21b08b0bfcc3cc4

Observe that we recreate the same address:
::

    $ sx stealth-uncover-secret $EPHEM_PUBKEY $SCAN_SECRET $SPEND_SECRET | sx pubkey | sx addr
    1BjqrpQqr4tY5YPQkL8aG7NGkFbTbiuVu

The secret can be converted into a WIF key which is a popular format for
importing into different Bitcoin wallets using the 'secret-to-wif' command.
::

    $ sx stealth-uncover-secret $EPHEM_PUBKEY $SCAN_SECRET $SPEND_SECRET | sx secret-to-wif
    KzUfPmcB7htVsbt18WA9SzyRdpXET63ppjVNEQyyEEXD9ChEQ4eD

Further understanding
---------------------

A stealth address consists of a scan key and optional spend keys. A single
spend key is useful for wallets that don't wish to decrypt constantly
to check for received payments which can compromise security. The scan key
allows wallets to check for received payments but not redeem the secret key.
::

    $ sx stealth-show-addr vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L
    Options: none
    Scan pubkey: 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    Spend pubkeys:
      024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    Number required signatures: 1
    Prefix: 0 0

And to recreate the stealth address:
::

    $ sx stealth-addr 031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006 024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    vJmwY32eS5VDC2C4GaZyXt7i4iCjzSMZ1XSd6KbkA7QbGE492akT2eZZMjCwWDqKRSYhnSA8Bgp78KeAYFVCi8ke5mELdoYMBNep7L

When Bob's wallet sends Alice a stealth payment, it generates a new ephemkey
and uses that create the Bitcoin address.
::

    $ EPHEM_SECRET=$(sx newkey | sx wif-to-secret)~$ SCAN_PUBKEY=031bab84e687e36514eeaf5a017c30d32c1f59dd4ea6629da7970ca374513dd006
    $ SPEND_PUBKEY=024c6988f8e64242a1b8f33513f5f27b9e135ad0a11433fc590816ff92a353a969
    $ sx stealth-initiate $EPHEM_SECRET $SCAN_PUBKEY $SPEND_PUBKEY 
    024609e569d3ce131a6b0c3c0a72c4bdfa5b25dc142b37e228d0ddd5ac0885ad6b
    $ sx stealth-initiate $EPHEM_SECRET $SCAN_PUBKEY $SPEND_PUBKEY | sx addr
    1JF7ATY1pBQtvGSmNxiBUwKSZjzg5FkBjG

We can then repeat the same steps as before in the first section to create
the same address on Alice's side.
::

    $ sx stealth-uncover
    Usage: sx stealth-uncover EPHEM_PUBKEY SCAN_SECRET SPEND_PUBKEY
    $ EPHEM_PUBKEY=$(echo $EPHEM_SECRET | sx pubkey)
    $ sx stealth-uncover $EPHEM_PUBKEY $SCAN_SECRET $SPEND_PUBKEY | sx addr
    1JF7ATY1pBQtvGSmNxiBUwKSZjzg5FkBjG

Stealth math
------------

For deeper technical explanation see `DarkWallet stealth documentation <https://wiki.unsystem.net/index.php/DarkWallet/Stealth#Dual-key_stealth>`_.
We will go through the calculations with SX here.

We have:

SCAN_PUBKEY (Q) = SCAN_SECRET (d) * G

SPEND_PUBKEY (R) = SPEND_SECRET (f) * G

EPHEM_PUBKEY (P) = EPHEM_SECRET (e) * G

The stealth-initiate command is equivalent to:

SHARED_SECRET = sha256(EPHEM_SECRET * SCAN_PUBKEY)

PAY_PUBKEY = SPEND_PUBKEY + SHARED_SECRET * G

In SX the commands for Bob are:
::

    $ sx ec-multiply $EPHEM_SECRET $SCAN_PUBKEY 
    02859f5c0985ac6c8faed3547f557c8a8f532b301e3a6c963535a1f0206795231b
    $ sx ec-multiply $EPHEM_SECRET $SCAN_PUBKEY | sx sha256
    091ac68b47ce4ae30dbe585623b4cb2e3f41421cd14ffa341d29bc7d6cd3ce1c
    $ SHARED_SECRET=091ac68b47ce4ae30dbe585623b4cb2e3f41421cd14ffa341d29bc7d6cd3ce1c
    $ sx ec-tweak-add $SPEND_PUBKEY $SHARED_SECRET
    024609e569d3ce131a6b0c3c0a72c4bdfa5b25dc142b37e228d0ddd5ac0885ad6b
    $ sx ec-tweak-add $SPEND_PUBKEY $SHARED_SECRET | sx addr
    1JF7ATY1pBQtvGSmNxiBUwKSZjzg5FkBjG

Which is the same address as before.

The stealth-uncover command is equivalent to:

SHARED_SECRET = sha256(SCAN_SECRET * EPHEM_PUBKEY)

PAY_PUBKEY = SPEND_PUBKEY + SHARED_SECRET * G
::

    $ sx ec-multiply $SCAN_SECRET $EPHEM_PUBKEY 
    02859f5c0985ac6c8faed3547f557c8a8f532b301e3a6c963535a1f0206795231b
    $ sx ec-multiply $SCAN_SECRET $EPHEM_PUBKEY | sx sha256
    091ac68b47ce4ae30dbe585623b4cb2e3f41421cd14ffa341d29bc7d6cd3ce1c
    $ SHARED_SECRET=091ac68b47ce4ae30dbe585623b4cb2e3f41421cd14ffa341d29bc7d6cd3ce1c
    ...

The secret is equivalent to EC addition (mod prime) of SHARED_SECRET and SPEND_SECRET.
::

    $ sx ec-add-modp $SHARED_SECRET $SPEND_SECRET 
    dcb21e8dd5ee6971ed2bc7428cc5796e783af3f8107d48612dc894b12b686e42
    $ sx ec-add-modp $SHARED_SECRET $SPEND_SECRET | sx pubkey | sx addr
    1JF7ATY1pBQtvGSmNxiBUwKSZjzg5FkBjG

For more info see the `development documentation <https://wiki.unsystem.net/index.php/DarkWallet/Stealth>`_ for DarkWallet.

