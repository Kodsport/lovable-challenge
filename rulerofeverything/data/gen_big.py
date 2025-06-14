#!/usr/bin/python3

import sys
import random
import math
from random import randint
from functools import cmp_to_key

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

possible=int(cmdlinearg("possible"))

def eval(vids):
    vids.sort(key=cmp_to_key(lambda a, b: (a[1] * (b[1] - 1)) - (b[1] * (a[1] - 1))))
    s = 0
    for a,b in vids:
        s = s*a+b

    return s

t = int(8e9)

vids = []
while 1:
    any_update = False
    for i in range(100):
        vids_copy = [i for i in vids]
        vids_copy.append((randint(6, 10), randint(1, 10)))
        if eval(vids_copy)<t:
            vids = vids_copy
    if not any_update:
        break

print(len(vids),1)
for x in vids:
    print(*x)
print(eval(vids)+possible)
