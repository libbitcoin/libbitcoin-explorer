.. _tut-offlinetx:

********************
Offline Transactions
********************

Try this to make a mini-wallet.
::

    $ cd src/
    $ sx newkey
    5KPFsatiYrJcvCSRrDbtx61822vZjeGGGx3wu38pQDHRF8eVJ8H
    $ sx newkey > private.key
    $ cat private.key | sx addr
    134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz

Now send some funds to your address (0.001 BTC).

In this example we will send the funds to 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe.
::

    100000 Satoshis  (0.001 BTC) in total.
     90000 Satoshis (0.0009 BTC) to send.
     10000 Satoshis (0.0001 BTC) for the fee.

Use blockchain.info (or the history tool provided here) to lookup the
output for this address. Note down the transaction hash and transaction index.

Here is a screenshot of blockchain.info: http://i.imgur.com/dZvqJIV.png

We can see the tx hash is: ``97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3``
And there is a single output at index 1 that we want to spend.

Construct the transaction::

    $ sx mktx txfile.tx --input 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1 --output 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000

Because there is 100000 Satoshis going in, but only 9000 Satoshis out,
the remaining 10000 Satoshis (0.0001 BTC) will be taken by the Bitcoin
network as a fee. This is how fees work internally in Bitcoin.

`showtx` allows inspecting of tx files.
::

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

Note that the input script is empty.

We will now sign the first input using our private key.
::

    $ export DECODED_ADDR=$(cat private.key | sx addr | sx decode-addr)
    $ export SCRIPT_CODE=$(sx rawscript dup hash160 [ $DECODED_ADDR ] equalverify checksig)
    $ export SIGNATURE=$(cat private.key | sx sign-input txfile.tx 0 $SCRIPT_CODE)
    $ sx rawscript [ $SIGNATURE ] [ $(cat private.key | sx pubkey) ] | sx set-input txfile.tx 0
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

Now the input script is prepared, and the tx is signed.

Put ``txfile.tx`` on a USB stick, transport it to your online computer.

Broadcast the final tx to the Bitcoin network.
::

    $ sx broadcast-tx txfile.tx

Or to send it to one Bitcoin node (like a localhost one), use:
::

    $ sx sendtx txfile.tx localhost 4009

