Hi!

My aim with this project is to provide a set of modular Bitcoin
commandline utilities, that admin types can engage with Bitcoin
functionality without having to write code.

By chaining all these commands together in different ways, you can do
offline transactions, maintain a wallet, work with deterministic keys, ...

It would be cool to see Bitcoin wallets written in bash script using
these tools to handle the core functionality. I believe the more we
give good tools to the community, the more we can decentralise
development and increase access to the core technology for all types.

Use this bash shell script to install sx: http://sx.dyne.org/install-sx.sh

Cheat sheet:

  http://i.imgur.com/8R0cfuw.png

To see a list of the sx commands type:

    $ sx help


Simple Bitcoin Client
---------------------

Try this to make a mini-wallet.

    $ cd src/
    $ sx newkey
    5KPFsatiYrJcvCSRrDbtx61822vZjeGGGx3wu38pQDHRF8eVJ8H
    $ sx newkey > private.key
    $ cat private.key | sx addr
    134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz

Now send some funds to your address (0.001 BTC).

In this example we will send the funds to 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe.

  100000 Satoshis  (0.001 BTC) in total.
   90000 Satoshis (0.0009 BTC) to send.
   10000 Satoshis (0.0001 BTC) for the fee.

Use blockchain.info (or the history tool provided here) to lookup the
output for this address. Note down the transaction hash and transaction index.

Here is a screenshot of blockchain.info: http://i.imgur.com/dZvqJIV.png

We can see the tx hash is:
97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3
And there is a single output at index 1 that we want to spend.

Construct the transaction:

    $ sx mktx txfile.tx --input 97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1 --output 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe:90000

Because there is 100000 Satoshis going in, but only 9000 Satoshis out,
the remaining 10000 Satoshis (0.0001 BTC) will be taken by the Bitcoin
network as a fee. This is how fees work internally in Bitcoin.

'showtx' allows inspecting of tx files.

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

Broadcast the final tx to the Bitcoin network.

    $ sx broadcast-tx txfile.tx

Or to send it to one Bitcoin node (like a localhost one), then use:

    $ sx sendtx txfile.tx localhost 4009


QR Code Generator
-----------------

    $ sudo apt-get install qrencode
    $ sx qrcode 13Ft7SkreJY9D823NPm4t6D1cBqLYTJtAe qrcode.png


Deterministic Wallet
--------------------

    $ sx newseed > wallet.seed
    $ cat wallet.seed
    b220b5bd2909df1d74b71c9e664233bf
    $ cat wallet.seed | sx mpk > master_public.key

Now you can generate your private keys for whatever number:

    $ cat wallet.seed | sx genpriv 0
    5Jmb4EYzEqj63rkPwADFY7WyGV2kga3YB1HfDAzg9dHNG57NMPu
    $ cat wallet.seed | sx genpriv 1
    5KjCYpPyxU2e88S57b1naKUsJ1JNjCudkFSQPxqcYyBYgzzahNe

You can use either the master_public.key or the wallet.seed for generating
Bitcoin receive addresses. But you cannot use the master_public.key for
generating the private keys for spending those Bitcoins.

    $ cat master_public.key | sx genpub 0
    1a4b47AC4ydSnAAcTNH1qozHq2pwJb644
    $ cat wallet.seed | sx genpub 0
    1a4b47AC4ydSnAAcTNH1qozHq2pwJb644

For Electrum compatible 12 word seeds, use the mnemonic tool.

    $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic
    people blonde admit dart couple different truth common alas stumble time cookie
    $ echo "people blonde admit dart couple different truth common alas
    stumble time cookie" | sx mnemonic
    148f0a1d77e20dbaee3ff920ca40240d


balance/history (Advanced)
--------------------------

The balance/history tools use a network connection to make requests
against the load balancer backend.

    $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx balance
    100000
    $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx history
    Output Hash:Index                           Output Height   Value (Satoshis) Spend Hash:Index                Spend Height
    97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1  247683 100000      Unspent                                 230529504

It's possible to run as many backend workers as you like. The
load balancer (obbalancer) will distribute requests evenly among the backends.
Use worker-output.sh to view debug info from the worker. Each worker must
have their own unique copy of the blockchain database.

See the Obelisk config files in /usr/local/etc/obelisk/. The sx config file
is stored at ~/.sx.cfg (there's an example at /usr/local/share/sx.cfg).
You can change this configuration parameter in Obelisk using
'./configure --sysconfigdir=/etc/'. By configuring different workers and load
balancers, you can run multiple setups on the same host. By default it is now
pointing at my development server, but I will change this soon and migrate to
a new host. Also I make no guarantees about stability or compatibility.

Multisignature N-M Transactions
-------------------------------

This example will create a 2-3 multisignature transaction but these
instructions can be easily generalised for other types.

Firstly we will create 3 keypairs.

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

    $ sx rawscript 2 [ $(cat key1 | sx pubkey) ] [ $(cat key2 | sx pubkey) ] [
    $(cat key3 | sx pubkey) ] 3 checkmultisig > msig.script

The file 'msig.script' now stores the hex representation of that script.
We can display it at anytime using:

    $ cat msig.script | sx showscript
    2 [ 04cb9c3c222c5f7a7d3b9bd152f363a0b6d54c9eb312c4d4f9af1e8551b6c421a6a4ab0e29105f24de20ff463c1c91fcf3bf662cdde4783d4799f787cb7c08869b ] [ 04ccc588420deeebea22a7e900cc8b68620d2212c374604e3487ca08f1ff3ae12bdc639514d0ec8612a2d3c519f084d9a00cbbe3b53d071e9b09e71e610b036aa2 ] [ 04ab47ad1939edcb3db65f7fedea62bbf781c5410d3f22a7a3a56ffefb2238af8627363bdf2ed97c1f89784a1aecdb43384f11d2acc64443c7fc299cef0400421a ] 3 checkmultisig

Now we generate the multisignature Bitcoin address (which always begins
with the number 3):

    $ cat msig.script | sx scripthash
    34CRZpt8j81rgh9QhzuBepqPi4cBQSjhjr

Send some bitcoin to that address!

This is my transaction:

https://blockchain.info/tx/e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52


## Spending the multisignature coins

We create the basic transaction.

    $ sx mktx txfile.tx -i e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0 -o 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY:9900000
    Added input e2124d25a7f6fe0d5dd5dd78ba7d98f60f8c47be9c91699e649e04118d531f52:0
    Added output sending 9900000 Satoshis to 1Fufjpf9RM2aQsGedhSpbSCGRHrmLMJ7yY.

The transaction has a fee of 0.001 BTC and is saved in the file named
'txfile.tx'.

It has a single input which we will generate the signatures for, create the
script and then set the input.

Use the sx command 'showtx' to show a transaction.

In our example we will emit the first signature and only use key2 and key3.

We use the opcode 'zero' to represent the emitted signature of key1.

Sign an input using:

    $ cat key2 | sx sign-input txfile.tx 0
    3046022100a147c529f7dfa291ceb2c2f21094ca101a1cfe7036cda18935d6899111cad76b022100c0d6392bdd9b31e0e3fe13dce3d928cf6857b411b6e05f35f12403b877c26bad01
    $ cat key3 | sx sign-input txfile.tx 0
    3046022100957f0bfdd476f2d8985268d7964168f6b7e43f54089f8fbff35a4f62e7a221f9022100be8f565e30781d353d71f54202009fe14b8203151d235ba6bf3db2b531680bca01

Our example will use bash substitution again.

    $ sx rawscript zero [ $(cat key2 | sx sign-input txfile.tx 0 $(cat msig.script)) ] [ $(cat key3 | sx sign-input txfile.tx 0 $(cat msig.script)) ] [ $(cat msig.script) ] | sx set-input txfile.tx 0

The transaction is finalised! Broadcast it:

    $ sx broadcast-tx txfile.tx

https://blockchain.info/tx/d646f82bd5fbdb94a36872ce460f97662b80c3050ad3209bef9d1e398ea277ab

