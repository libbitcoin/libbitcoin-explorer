#!/usr/bin/python
import sys, re, json, os

lines = os.popen('sx history '+' '.join(sys.argv[1:-1])).readlines()

# Convert to float or int if possible, otherwise leave as string
def attempt_num(x):
    if re.match('^(-|)[0-9]*(|\.[0-9]*)$',x): return float(x) if '.' in x else int(x)
    else: return x

# Create objects
txo = []
obj = {}
for i in range(len(lines)):
    indent = len(re.match('^ *',lines[i]).group(0))
    fields = [x for x in lines[i].strip().split(' ') if x]
    if len(fields) < 2:
        continue
    if indent == 0:
        if obj: txo.append(obj)
        obj = {}
    obj[fields[0][:-1]] = attempt_num(fields[1])
    obj["$txt"] = obj.get("$txt","") + lines[i]

if obj: txo.append(obj)

utxo = [x for x in txo if x["spend"] == "Unspent"]

val = int(sys.argv[-1])

high = sorted([x for x in utxo if x["value"] >= val], key=lambda x: x["value"])
low = sorted([x for x in utxo if x["value"] < val], key=lambda x: -x["value"])

if len(high) > 0:
    # Look for a single utxo to pay for the whole transaction if possible
    print high[0]["$txt"]
else:
    # Go through smaller outputs highest to lowest
    tot,ans = 0,[]
    for txo in low:
        ans.append(txo)
        tot += txo["value"]
        if tot >= val: break
    if tot < val: print "Not enough UTXO; only accumulated %d out of %d" % (tot,val)
    else: print '\n\n'.join([x["$txt"] for x in ans])
