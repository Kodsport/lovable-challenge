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

def rec(maxa, maxn):
    assert min(maxa, maxn) > 0
    if maxa == 1 or maxn == 1:
        return [1]
    
    while True:
        d = random.randrange(0, 30)
        c = 0
        while 2**(d+c+1) <= maxa and 2**(c+1) <= maxn:
            if random.randint(0,3) == 0:
                break
            c += 1
        if 2**(d+c) <= maxa and 2**c <= maxn:
            copies = 2**c
            maxa2 = 2**d
            if maxa2 > 1 and random.randint(0,1) == 1:
                maxa2 // 2
            base = rec(maxa2, maxn // (2**c))
            ans = []
            for i in range(copies):
                base2 = base.copy()
                for j in range(len(base2)):
                    base2[j] += (2**d)*i
                ans += base2
            return ans
            

MAXN = 5 * 10**5
MAXS = 10**9

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n', MAXN))
s = int(cmdlinearg('s', MAXS))
mode = cmdlinearg('mode', "random")
s = max(s, n)
S = []

if mode == "random":
    S = list(random.sample(range(1, s+1), n))
elif mode == "two":
    x = int(cmdlinearg('x'))
    shift = int(cmdlinearg('shift',0))
    S = [1+shift, x+shift]
    n = 2
elif mode == "power":
    assert n%2 == 0
    p = int(cmdlinearg('p'))
    p_max = 1
    while 2*p_max < s:
        p_max *= 2
    s_set = set()
    s_set.add(1)
    s_set.add(p_max+1)

    tries = 0
    while len(s_set) < n:
        r = random.randrange(0, 2**p)

        diff = random.randint(1, p_max // (2**(p+1))) * 2**p
        x1 = random.randint(1, p_max-diff)
        x2 = x1+diff

        if x1 not in s_set and x2 not in s_set and x2 < p_max+1:
            s_set.add(x1)
            s_set.add(x2)
            tries = 0
        else:
            tries += 1
        if tries > 100:
            break
    S = list(s_set)
    n = len(S)

elif mode == "ap":
    d = int(cmdlinearg('d'))
    S.append(1)
    while len(S) < n:
        S.append(S[-1]+d)
    extra = random.randint(0, s-S[-1])
    for i in range(n):
        S[i] += extra

elif mode == "recursive":
    S = rec(s, n)
    n = len(S)
    
elif mode == "lucas":
    x = int(cmdlinearg('x'))
    gap = int(cmdlinearg('gap'))
    c = int(cmdlinearg('c'))
    L = []
    for i in range(0, x):
        if i|(x-1) == (x-1):
            L.append(i+1)
    for i in range(c):
        L2 = L.copy()
        for j in range(len(L2)):
            L2[j] += gap*i
        S += L2
    n = len(S)

print(n)
print(*S)

