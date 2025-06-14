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

print(n,q)
taken = 0
for i in range(2, n):
    p = 1
    while taken < n//2 and p <= 8e9:
        print(i, randint(1, 100))
        p *= i
        taken += 1

while taken < n:
    print(1, randint(1, maxb))
    taken += 1

qs = []
maxv = math.log(8e9)
for i in range(q):
    qs.append(round(math.exp(random.uniform(0, maxv))))
print(*qs)
