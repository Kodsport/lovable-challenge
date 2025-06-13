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


MAXN = 3 * 10**5


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
N = int(cmdlinearg('N', MAXN))
MAXA = int(cmdlinearg('MAXA', 1e9))

mode = cmdlinearg('mode', "random")

if mode == "random":
    a = [random.randint(1,MAXA) for _ in range(N)]
else:
    assert(0), "mode does not exist"

print(N)
#random.shuffle(a)
print(*a)

