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

    $ sx rawscript 2 [ $(cat key1 | sx pubkey) ] [ $(cat key2 | sx pubkey) ] [ $(cat key3 | sx pubkey) ] 3 checkmultisig > msig.script

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

Send some bitcoin to that address!

This is my transaction:

https://blockchain.info/tx/e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52

Spending the multisignature coins
---------------------------------

We create the basic transaction.
::

    $ sx mktx txfile.tx -i e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0 -o 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY:9900000
    Added input e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0
    Added output sending 9900000 Satoshis to 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY.

The transaction has a fee of 0.001 BTC and is saved in the file named
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


