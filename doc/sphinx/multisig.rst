.. _tut-multisig:

*******************************
Multisignature MN Transactions
*******************************

This example will create a 2-3 multisignature transaction but these
instructions can be easily generalised for other types.

Firstly we will create 3 keypairs.
::

    $ sx newkey > key1
    $ cat key1 | sx addr
    15xG6FE45vjuEdQQamvvgRPzrdzvZAxAyJ
    $ sx newkey > key2
    $ cat key2 | sx addr
    12GhrHLu4K5LL8hNkyMZZXz3u7QJc5Qjsc
    $ sx newkey > key3
    $ cat key3 | sx addr
    1KWv6rPrXzggQNkQrz8Leq1DhDm1b3y23r

For multisignature stuff we will need to use the public keys of the keypairs.
We use bash substitution below for convenience.
::

    $ PUBKEY1=$(cat key1 | sx pubkey)
    $ PUBKEY2=$(cat key2 | sx pubkey)
    $ PUBKEY3=$(cat key3 | sx pubkey)
    $ sx rawscript 2 [ $PUBKEY1 ] [ $PUBKEY2 ] [ $PUBKEY3 ] 3 checkmultisig > msig.script

The file 'msig.script' now stores the hex representation of that script.
We can display it at anytime using:
::

    $ cat msig.script | sx showscript
    2 [ 04cb9c3c222c5f7a7d3b9bd152f363a0b6d54c9eb312c4d4f9af1e8551b6c421a6a4ab0e29105f24de20ff463c1c91fcf3bf662cdde4783d4799f787cb7c08869b ] [ 04ccc588420deeebea22a7e900cc8b68620d2212c374604e3487ca08f1ff3ae12bdc639514d0ec8612a2d3c519f084d9a00cbbe3b53d071e9b09e71e610b036aa2 ] [ 04ab47ad1939edcb3db65f7fedea62bbf781c5410d3f22a7a3a56ffefb2238af8627363bdf2ed97c1f89784a1aecdb43384f11d2acc64443c7fc299cef0400421a ] 3 checkmultisig

Now we generate the multisignature Bitcoin address (which always begins
with the number 3):
::

    $ cat msig.script | sx scripthash
    34CRZpt8j81rgh9QhzuBepqPi4cBQSjhjr

Send 0.001 BTC to that address!

This is my transaction:

https://blockchain.info/tx/e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52

Spending the multisignature coins
---------------------------------

We create the basic transaction.
::

    $ sx mktx txfile.tx -i e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0 -o 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY:90000
    Added input e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0
    Added output sending 9900000 Satoshis to 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY.

The transaction has a fee of 0.0001 BTC and is saved in the file named
`txfile.tx`.

It has a single input which we will generate the signatures for, create the
script and then set the input.

Use the sx command `showtx` to show a transaction.

In our example we will emit the first signature and only use key2 and key3.

We use the opcode ``zero`` to represent the emitted signature of key1.

Sign an input using::

    $ cat key2 | sx sign-input txfile.tx 0 $(cat msig.script)
    3046022100a147c529f7dfa291ceb2c2f21094ca101a1cfe7036cda18935d6899111cad76b022100c0d6392bdd9b31e0e3fe13dce3d928cf6857b411b6e05f35f12403b877c26bad01
    $ cat key3 | sx sign-input txfile.tx 0 $(cat msig.script)
    3046022100957f0bfdd476f2d8985268d7964168f6b7e43f54089f8fbff35a4f62e7a221f9022100be8f565e30781d353d71f54202009fe14b8203151d235ba6bf3db2b531680bca01

Our example will use bash substitution again.
::

    $ SIGNATURE2=$(cat key2 | sx sign-input txfile.tx 0 $(cat msig.script))
    $ SIGNATURE3=$(cat key3 | sx sign-input txfile.tx 0 $(cat msig.script))
    $ INPUT_SCRIPT=$(sx rawscript zero [ $SIGNATURE2 ] [ $SIGNATURE3 ] [ $(cat msig.script) ])
    $ sx set-input txfile.tx 0 $INPUT_SCRIPT > signed.tx

The transaction is finalised! Broadcast it.
::

    $ sx sendtx-p2p signed-tx

Or send it to one Bitcoin node (like a localhost one).
::

    $ sx sendtx-node signed-tx localhost 4009

Or to send it through the ``blockchain.info/pushtx'' service.
::

    $ sx sendtx-bci signed-tx

Or to send it via an obelisk server.
::

    $ sx sendtx-obelisk signed-tx

https://blockchain.info/tx/d646f82bd5fbdb94a36872ce460f97662b80c3050ad3209bef9d1e398ea277ab

Generalizing for M of N expressions
-----------------------------------

Many mining pools and Bitcoin nodes currently do not support some types of
Bitcoin transactions. However a few mining pools do such as eligius which
we encourage developers and users to support however they can.

You can post transactions to eligius using the pushtxn interface.

http://eligius.st/~wizkid057/newstats/pushtxn.php

Here's an example of creating a 3 of 5 multisignature transaction.
::

    $ sx newkey > key1
    $ sx newkey > key2
    $ sx newkey > key3
    $ sx newkey > key4
    $ sx newkey > key5
    $ PUBKEY1=$(cat key1 | sx pubkey)
    $ PUBKEY2=$(cat key2 | sx pubkey)
    $ PUBKEY3=$(cat key3 | sx pubkey)
    $ PUBKEY4=$(cat key4 | sx pubkey)
    $ PUBKEY5=$(cat key5 | sx pubkey)
    $ sx rawscript 3 [ $PUBKEY1 ] [ $PUBKEY2 ] [ $PUBKEY3 ] [ $PUBKEY4 ] [ $PUBKEY5 ] 5 checkmultisig > msig.script
    $ cat msig.script | sx scripthash
    3267gLrEz8URAUxjrHqk7aQD3Nv1A9at8j

Now I deposit 0.001 BTC to that address before continuing::

    $ sx mktx --input 01a7836061aa1aae9da07bbf3c85277a4b310dcb0ebcb289740b9d31d36e12eb:0 -o 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY:90000
    mktx: Action '01a7836061aa1aae9da07bbf3c85277a4b310dcb0ebcb289740b9d31d36e12eb:0' doesn't exist.
    $ sx mktx txfile.tx -i 01a7836061aa1aae9da07bbf3c85277a4b310dcb0ebcb289740b9d31d36e12eb:0 -o 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY:90000
    Added input 01a7836061aa1aae9da07bbf3c85277a4b310dcb0ebcb289740b9d31d36e12eb:0
    Added output sending 90000 Satoshis to 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY.
    $ SIGNATURE3=$(cat key3 | sx sign-input txfile.tx 0 $(cat msig.script))
    $ SIGNATURE4=$(cat key4 | sx sign-input txfile.tx 0 $(cat msig.script))
    $ SIGNATURE5=$(cat key5 | sx sign-input txfile.tx 0 $(cat msig.script))
    $ INPUT_SCRIPT=$(sx rawscript zero zero [ $SIGNATURE3 ] [ $SIGNATURE4 ] [ $SIGNATURE5 ] [ $(cat msig.script) ])
    $ sx set-input txfile.tx 0 $INPUT_SCRIPT > signed.tx
    $ cat signed.tx | sx showtx
    hash: 408c742365929794525590772475d090e6b3a452fa8f97c376978f068eb07bfd
    version: 1
    locktime: 0
    Input:
      previous output: 01a7836061aa1aae9da07bbf3c85277a4b310dcb0ebcb289740b9d31d36e12eb:0
      script: zero [ 3045022100e5afa15cbb67e648cd25d779300b512c455dcfb467bc8db2bb93b2c7818bdb6e022032f06f99909308777ca80205c88477aaba96bcca895059c9883c87859c0e2eb101 ] [ 304402207033c4969e9aa44821bf64590bf3e242e58a7c1a6fa96bc0c0e293934814a340022078958317e9ffc3761398231cee91ba2d16b8969eb12aec78632d9cf1152ab71301 ] [ 3045022031dc9c62121267e838ac834181e8e301506c706bfd5e59d2eb352fbf498c5ab9022100b3dea57d7b239d59fe4843e390860e3556d64cbf15e10c19483f1451ab9f9f7c01 ] [ 5321038f85c1e06acd49da7071d0f861ea4be4e23d2a1c4f02a3d59232837788559200210282ac9b9362eb7df54f1c1985d32ee54ed095e3bd9b3e7a37f3ed680b0e3da5f121029391178193d15a2ae88cc44d1bc1ed4401db3bab2c84d7ab5885a5f745aa95182102e5bdba47e3d78c933c6b616dc686341308646fed4031f9fcd10f1199c0bb1a4421021a301941eefdf88e59a0fc67e40f9fb40227990e09da42e4c74a7ea425a1898955ae ]
      sequence: 4294967295
      address: 3267gLrEz8URAUxjrHqk7aQD3Nv1A9at8j
    Output:
      value: 90000
      script: dup hash160 [ a387ba64648b2c78b38d5278a43f0291a06458f0 ] equalverify checksig
      address: 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY
    $ cat signed.tx | sx validtx
    Status: Success
      Unconfirmed: 0

Finally I submit the transaction to eligius.
::

    Trying to send...
    array(3) {
      ["result"]=>
      string(64) "408c742365929794525590772475d090e6b3a452fa8f97c376978f068eb07bfd"
      ["error"]=>
      NULL
      ["id"]=>
      string(1) "1"
    }
    Response = 0

