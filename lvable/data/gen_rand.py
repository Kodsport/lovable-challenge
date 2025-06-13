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


MAXN = 5 * 10**5


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
N = int(cmdlinearg('N', MAXN))

alfa = "qwertyuiopasdfghjklzxcvbnm"

mode = cmdlinearg('mode', "random")

if mode == "random":
    s = [random.choice(alfa) for _ in range(N)]
    s = "".join(s)

elif mode == "nolv":
    s = []
    while len(s) < N:
        s.append(random.choice(alfa))

        if len(s) > 1:
            if s[-2] == "l" and s[-1] == "v":
                s.pop()
                s.pop()
    
    s = "".join(s)

elif mode == "nolnov":
    s = []
    while len(s) < N:
        s.append(random.choice(alfa))

        
        if s[-1] == "l" or s[-1] == "v":
            s.pop()
    
    s = "".join(s)

else:
    assert(0), "mode does not exist"

print(N)
#random.shuffle(a)
print(s)

