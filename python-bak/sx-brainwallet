#!/usr/bin/python
import  sys, subprocess, hashlib
PIPE = subprocess.PIPE

def runcmd(args,inp=''):
    p = subprocess.Popen(args, stdout=PIPE, stdin=PIPE, stderr=PIPE)
    return p.communicate(input=inp)[0]

args, opts = [], {}
i = 1
while i < len(sys.argv):
    if sys.argv[i][0:2] == '--':
        opts[sys.argv[i][2:]] = sys.argv[i+1]
        i += 2
    else:
        args.append(sys.argv[i])
        i += 1

if len(args) == 0: seed = ''
elif len(args) == 1: seed = args[0]
else: seed = args[0] + ':' + args[1]

def sha256(x): return hashlib.sha256(x).hexdigest()

def slowsha(x,rounds=1000):
    old, new = x, ''
    for i in range(rounds):
        new = hashlib.sha256(old).digest()
        old = new+x
    return new.encode('hex')

if opts.get('algo','') == 'slowsha': algo = slowsha
elif opts.get('rounds',None): algo = lambda x: slowsha(x,int(opts['rounds']))
else: algo = sha256

print runcmd(['sx','base58check-encode',algo(seed),'128']).strip()
