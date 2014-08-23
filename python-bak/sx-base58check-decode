#!/usr/bin/python
import subprocess, sys
PIPE = subprocess.PIPE
p = subprocess.Popen(['sx','base58-decode']+sys.argv[1:], stdout=PIPE, stdin=PIPE, stderr=PIPE)
med = p.communicate(input=sys.stdin.read() if len(sys.argv) == 1 else '')[0]
p2 = subprocess.Popen(['sx','unwrap',med], stdout=PIPE, stdin=PIPE, stderr=PIPE)
print p2.communicate(input='')[0].strip()
