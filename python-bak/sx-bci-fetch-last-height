#!/usr/bin/python

import urllib, urllib2, json, sys, random

opener = urllib2.build_opener()
opener.addheaders = [('User-agent', 'Mozilla/5.0'+str(random.randrange(1000000)))]

text = opener.open('http://blockchain.info/latestblock').read()

try:
    jsonobj = json.loads(text)
    print jsonobj["height"]
except:
    sys.stderr.write("Bad JSON")
    sys.exit(-1)
