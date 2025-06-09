#!/usr/bin/python3

import sys
import random
import math
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


MAXM = 5 * 10**5


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
m = int(cmdlinearg('M', MAXM))

mode = cmdlinearg('mode', "random")
alfa = "NWSE"
a = cmdlinearg("a","")

if a:
    assert(m == len(a))
    print(m)
    print(a)
    exit()

elif mode == "random":
    
    n = int(cmdlinearg('n', 0))
    w = int(cmdlinearg('w', 0))
    s = int(cmdlinearg('s', 0))
    e = int(cmdlinearg('e', 0))
    a = [] + ["N"]*n + ["W"]*w + ["S"]*s + ["E"]*e
    
    while len(a) < m:
        a.append(alfa[random.randint(0,3)])
        
    
elif mode == "onlytwo":
    alfa = "NE"
    a = [alfa[random.randint(0,1)] for _ in range(m)]
else:
    assert(0), "mode does not exist"

print(m)
random.shuffle(a)
print("".join(a))

