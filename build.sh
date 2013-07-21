#!/bin/bash
# Create new private key.
cd newpriv
make
cd ..
echo "Compiled newpriv"
# Show Bitcoin address of a private key.
cd showpriv
make
cd ..
echo "Compiled showpriv"
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
# These 2 tools depend on Obelisk: http://github.com/genjix/obelisk
#cd balance
#make
#cd history
#make

