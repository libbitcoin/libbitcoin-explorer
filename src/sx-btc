#!/usr/bin/python
import sys
from decimal import Decimal as D

if len(sys.argv) != 2:
    print >> sys.stderr, "Usage: sx btc SATOSHIS"
    sys.exit(-1)
print "%.8f" % (D(sys.argv[1]) * D(10)**-8)
sys.exit(0)

