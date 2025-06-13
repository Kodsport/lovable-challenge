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

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
g = int(cmdlinearg('g'))
maxk = int(cmdlinearg('maxk', 1e9))

k = randint(1, maxk)
print(n,k)
taken = 0
for i in range(1, n+1):
    for j in range(g):
        if taken >= n:
            break
        print(i, randint(1, 100))
        taken += 1

