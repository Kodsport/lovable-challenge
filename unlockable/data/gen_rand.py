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

# https://github.com/cheran-senthil/PyRival/blob/master/pyrival/algebra/is_prime.py
def is_prime(n):
    """returns True if n is prime else False"""
    if n < 5 or n & 1 == 0 or n % 3 == 0:
        return 2 <= n <= 3
    s = ((n - 1) & (1 - n)).bit_length() - 1
    d = n >> s
    for a in [2, 325, 9375, 28178, 450775, 9780504, 1795265022]:
        p = pow(a, d, n)
        if p == 1 or p == n - 1 or a % n == 0:
            continue
        for _ in range(s):
            p = (p * p) % n
            if p == n - 1:
                break
        else:
            return False
    return True


MAXN = 2 * 10**5


random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('N', MAXN))
MAXA = int(cmdlinearg('MAXA',1e9))

prime = int(cmdlinearg('prime',0))

mode = cmdlinearg('mode', "random")

a = int(cmdlinearg('a', random.randint(2,MAXA)))

# Ensure that a is prime
while not is_prime(a) and prime:
    a = random.randint(2,MAXA)
    

if mode == "random":
    b = [random.randint(1,MAXA) for _ in range(n)]
elif mode == "unique":
    b = set()
    while len(b) < n:
        b.add(random.randint(1,MAXA))
    b = list(b)
elif mode == "dense":
    b = set()
    while len(b) < n:
        candx = random.randint(1,round(math.log(MAXA,a)-1))
        cand = random.randint(1,MAXA//(a**candx))*a**candx
        if cand <= MAXA:
            b.add(cand)
    b = list(b)
else:
    assert 0, "mode does not exist"

random.shuffle(b)
print(n,a)
print(*b)
