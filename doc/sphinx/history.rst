.. _tut-history:

***************
balance/history
***************

The balance/history tools use a network connection to make requests
against the load balancer backend.
::

    $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx balance
    100000
    $ echo 134HfD2fdeBTohfx8YANxEpsYXsv5UoWyz | sx history
    Output Hash:Index                           Output Height   Value (Satoshis) Spend Hash:Index                Spend Height
    97e06e49dfdd26c5a904670971ccf4c7fe7d9da53cb379bf9b442fc9427080b3:1  247683 100000      Unspent                                 230529504

It's possible to run as many backend workers as you like. The
load balancer (obbalancer) will distribute requests evenly among the backends.
Use `worker-output.sh` to view debug info from the worker. Each worker must
have their own unique copy of the blockchain database.

See the Obelisk config files in `/usr/local/etc/obelisk/`. The sx config file
is stored at `~/.sx.cfg` (there's an example at `/usr/local/share/sx.cfg`).
You can change this configuration parameter in Obelisk using
`./configure --sysconfigdir=/etc/`. By configuring different workers and load
balancers, you can run multiple setups on the same host. By default it is now
pointing at my development server, but I will change this soon and migrate to
a new host. Also I make no guarantees about stability or compatibility.

