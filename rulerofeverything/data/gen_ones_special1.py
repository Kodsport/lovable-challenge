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
q = int(cmdlinearg('q', 5))
maxb = int(cmdlinearg('maxb', 5))
num_twos = int(cmdlinearg('num_twos', 32))
lo_v = int(cmdlinearg('lo_v', 0))

print(n,q)
taken = 0
for i in range(2, num_twos):
    taken += 1
    print(2, randint(1, 5))

while taken < n:
    print(1, randint(1, maxb))
    taken += 1

qs = []
maxv = math.log(8e9)
for i in range(q):
    qs.append(round(math.exp(random.uniform(lo_v, maxv))))
print(*qs)
