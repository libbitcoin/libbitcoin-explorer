.. _tut-hdkeys:

***************
HD Keys (BIP32)
***************

HD keys come in both public and private flavors, which can be serialized into base58. It is farily easy to see which is which by looking at the prefix:
::

    xpub661MyMwAqRbcFtXgS5sYJABqqG9YLmC4Q1Rdap9gSE8NqtwybGhePY2gZ29ESFjqJoCu1Rupje8YtGqsefD265TMg7usUDFdp6W1EGMcet8

    xprv9s21ZrQH143K3QTDL4LXw2F7HEK3wJUD2nW2nRk4stbPy6cq3jPPqjiChkVvvNKmPGJxWUtg6LnF5kejMRNNU3TGtRBeJgk33yuGBxrMPHi

There are three basic operations:

* Generate an HD private key from entropy (used to start the chain)
* Generate an HD private key from another private HD key
* Generate an HD public key from either a public or private HD key

The operations for generating child keys take an integer to indicate which key is in question. If the integer is >= 2^31 (i.e. MSB set), a different (secure) derivation algorithm is used. Since typing these big numbers is hard, the command line should accept a flag like "--hard" which effectively adds 2^31 to the integer.
::

    $ sx hd-seed [<entropy>]
    xprv9s21Z...
    $ echo $PRIVKEY | sx hd-priv <integer> [--hard]
    xprv9s21Z...
    $ echo $PRIVKEY/$PUBKEY | sx hd-pub <integer> [--hard]
    xpub661MyMwA...

The keys aren't provided on the command line, they come from stdin. This would allow generating deep keys like so:
::

    # Find m/0/0/1H:
    $ cat my-seed-file | sx hd-seed | sx hd-priv 0 | sx hd-priv 0 | sx hd-priv 1 --hard
    xpub661MyMwAqRbc...

This covers the major functionality found in the BIP. On the other hand, none of the other tools in the sx suite know what to do with these keys. At the very least, we need the following two commands:
::

    $ echo $PRIVKEY/$PUBKEY | sx hd-to-address
    19z88...
    $ echo $PRIVKEY | sx hd-to-wif
    K51at409...

