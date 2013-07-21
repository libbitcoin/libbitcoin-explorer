#!/bin/bash
# Create new private key.
cd newpriv
make
cd ..
echo "Compiled newpriv"
# Show Bitcoin address of a private key.
cd addr
make
cd ..
echo "Compiled addr"
# Construct a transaction.
cd mktx
make
cd ..
echo "Compiled mktx"
# Show a transaction.
cd showtx
make
cd ..
echo "Compiled showtx"
# Sign tx input
cd sign-input
make
cd ..
echo "Compiled sign-input"
# Broadcast a transaction.
cd broadcast-tx
make
cd ..
echo "Compiled broadcast-tx"
# Send a transaction to a specific node
# Useful for debugging by sending to a node you own.
cd send-tx
make
cd ..
echo "Compiled send-tx"
# Create new deterministic wallet
cd newseed
make
cd ..
echo "Compiled newseed"
# Get master public key from a seed
cd mpk
make
cd ..
echo "Compiled mpk"
# Generate a private key from a seed, number and optional for_change flag.
cd genpriv
make
cd ..
echo "Compiled genpriv"
# Generate an address from a master pubkey, number and optional for_change flag.
cd genpub
make
cd ..
echo "Compiled genpub"
# These 2 tools depend on Obelisk: http://github.com/genjix/obelisk
#cd balance
#make
#cd history
#make

mkdir -p bin
cp newpriv/newpriv bin/
cp addr/addr bin/
cp mktx/mktx bin/
cp showtx/showtx bin/
cp sign-input/sign-input bin/
cp broadcast-tx/broadcast-tx bin/
cp send-tx/send-tx bin/
cp newseed/newseed bin/
cp mpk/mpk bin/
cp genpriv/genpriv bin/
cp genpub/genpub bin/
echo "Copied binaries to bin/"

