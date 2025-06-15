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
k = int(cmdlinearg('k', 26))

import string
alfa = string.ascii_lowercase[:k]

mode = cmdlinearg('mode', "random")

if mode == "random":
    a = [random.choice(alfa) for _ in range(n)]
    a = "".join(random.choices(alfa, k=n))

    b = [random.choice(alfa) for _ in range(n)]
    b = "".join(random.choices(alfa, k=n))
elif mode == "repeats":
    s = cmdlinearg("s")
    occs = n//len(s)
    a = s * occs
    b = s[::-1] * occs
elif mode == "long_common_prefix":
    common_prefix_len = n // 2
    prefix = "".join(random.choices(alfa, k=common_prefix_len))
    a = prefix + "".join(random.choices(alfa, k=n - common_prefix_len))
    b = prefix + "".join(random.choices(alfa, k=n - common_prefix_len))
elif mode == "interleaved":
    lcs_len = n // 2
    lcs_chars = random.choices(alfa, k=lcs_len)
    
    a_list = []
    b_list = []
    
    a_extra_chars = random.choices(alfa, k=n - lcs_len)
    b_extra_chars = random.choices(alfa, k=n - lcs_len)
    
    for i in range(lcs_len):
        a_list.append(lcs_chars[i])
        b_list.append(lcs_chars[i])
        if i < len(a_extra_chars):
            a_list.append(a_extra_chars[i])
        if i < len(b_extra_chars):
            b_list.append(b_extra_chars[i])
            
    random.shuffle(a_list)
    random.shuffle(b_list)

    a = "".join(a_list[:n])
    b = "".join(b_list[:n])

elif mode == "sparse_matches":
    a_list = list(random.choices(alfa, k=n))
    b_list = list(random.choices(alfa, k=n))
    
    num_matches = min(n // 10, 5)
    for _ in range(num_matches):
        char_to_match = random.choice(alfa)
        idx_a = random.randint(0, n - 1)
        idx_b = random.randint(0, n - 1)
        a_list[idx_a] = char_to_match
        b_list[idx_b] = char_to_match
    a = "".join(a_list)
    b = "".join(b_list)

else:
    assert(0), f"mode {mode} does not exist"

if int(cmdlinearg('rev', 0)):
    a=a[::-1]
    b=b[::-1]

import subprocess
lcs = subprocess.run(["./lcsfast.out"], input=f"{a}\n{b}", text=True, capture_output=True).stdout.strip()
lcslen1 = subprocess.run(["./lcslen.out"], input=f"{a}\n{b}", text=True, capture_output=True).stdout.strip()
lcslen2 = subprocess.run(["./lcslen2.out"], input=f"{a}\n{b}", text=True, capture_output=True).stdout.strip()
#lcslen3 = subprocess.run(["./lcslen3.out"], input=f"{a}\n{b}", text=True, capture_output=True).stdout.strip()
assert(int(lcslen1)==int(lcslen2))
#assert(int(lcslen1)==int(lcslen3))
assert(len(lcs)==int(lcslen1))

print(a)
print(b)
print(lcs)

