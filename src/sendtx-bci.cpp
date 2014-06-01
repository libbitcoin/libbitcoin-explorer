//#!/usr/bin/python
//
//import urllib, urllib2, sys, urllib2, random
//
//if len(sys.argv) < 2: 
//    print "Need TX argument"
//    sys.exit(-1)
//
//if sys.argv[1] == "-":
//    txdata = sys.stdin.read().strip()
//else:
//    txdata = open(sys.argv[1]).read().strip()
//
//opener = urllib2.build_opener()
//opener.addheaders = [('User-agent', 'Mozilla/5.0'+str(random.randrange(1000000)))]
//
//url = 'http://blockchain.info/pushtx'
//form_data = {'tx': txdata }
//params = urllib.urlencode(form_data)
//try:
//    response = opener.open(url, params)
//    data = response.read()
//except Exception, e:
//    data = e.read().strip()
//
//if len(data) < 500:
//    print data
//    sys.exit(0)
//else:
//    sys.stderr.write(data)
//    sys.exit(-1)
