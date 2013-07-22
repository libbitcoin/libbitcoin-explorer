#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Usage: genqr ADDRESS"
    exit 1
fi
command -v qrencode >/dev/null 2>&1 || { echo >&2 "Please install 'qrencode'."; exit 1; }
ADDR=$1
qrencode bitcoin:$ADDR -o qrcode.png -s 10

