#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Usage: genqr ADDRESS"
fi
ADDR=$1
qrencode bitcoin:$ADDR -o qrcode.png -s 10

