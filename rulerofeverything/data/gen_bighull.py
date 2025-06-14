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
maxk = int(cmdlinearg('maxk', 1e9))
mink = int(cmdlinearg('mink', 1e9))
maxb = int(cmdlinearg('maxb', 1e9))

maxb = min(maxb, maxk-1)
lines = []
for i in range(2, n):
    b = i*(i+1)//2
    if b >= maxb:
        break
    lines.append(f"{i} {maxb - b}")
while len(lines) < n:
    lines.append(f"1 {randint(1, 100)}")
print(len(lines), q)
for line in lines:
    print(line)
print(*(randint(1, maxk) for i in range(q)))
