#!/usr/bin/python3

N, a = map(int,input().split())
b = set([*map(int,input().split())])
largest = max(list(b))

out = 0

for x in range(1,32):
    if a**x > largest:
        break
    for bb in b:
        if bb%(a**x) == 0:
            out += 1

print(out)
