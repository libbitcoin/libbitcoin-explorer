#!/bin/bash
if [ $# -ne 2 ]; then
    echo "Usage: genqr ADDRESS FILENAME"
    exit 1
fi
command -v qrencode >/dev/null 2>&1 || { echo >&2 "Please install 'qrencode'."; exit 1; }
ADDR=$1
FILE=$2
qrencode bitcoin:$ADDR -o $FILE -s 10

