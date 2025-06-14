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

print(n,q)
for i in range(n):
    print(randint(1, 5),randint(1, 100))
print(*(randint(1, maxk) for i in range(q)))
