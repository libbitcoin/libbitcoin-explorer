.. _tut-detwallet:

********************
Deterministic Wallet
********************

::

    $ sx newseed > wallet.seed
    $ cat wallet.seed
    b220b5bd2909df1d74b71c9e664233bf
    $ cat wallet.seed | sx mpk > master_public.key

Now you can generate your private keys for whatever number:
::

    $ cat wallet.seed | sx genpriv 0
    5Jmb4EYzEqj63rkPwADFY7WyGV2kga3YB1HfDAzg9dHNG57NMPu
    $ cat wallet.seed | sx genpriv 1
    5KjCYpPyxU2e88S57b1naKUsJ1JNjCudkFSQPxqcYyBYgzzahNe

You can use either the master_public.key or the wallet.seed for generating
Bitcoin receive addresses. But you cannot use the master_public.key for
generating the private keys for spending those Bitcoins.
::

    $ cat master_public.key | sx genpub 0
    1a4b47AC4ydSnAAcTNH1qozHq2pwJb644
    $ cat wallet.seed | sx genpub 0
    1a4b47AC4ydSnAAcTNH1qozHq2pwJb644

For Electrum compatible 12 word seeds, use the mnemonic tool.
::

    $ echo 148f0a1d77e20dbaee3ff920ca40240d | sx mnemonic
    people blonde admit dart couple different truth common alas stumble time cookie
    $ echo "people blonde admit dart couple different truth common alas stumble time cookie" | sx mnemonic
    148f0a1d77e20dbaee3ff920ca40240d

