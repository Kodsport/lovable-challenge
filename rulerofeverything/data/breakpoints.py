#!/usr/bin/python3

import sys
import random

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


# Generate n lines: each a (scale, shift) pair
# scale in [0.8, 1.2], shift in [-5, 5]
for _ in range(n):
    scale = random.uniform(0.8, 1.2)
    shift = random.uniform(-5, 5)
    print(f"{scale:.6f} {shift:.6f}")
