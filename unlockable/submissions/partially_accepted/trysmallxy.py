#!/usr/bin/python3

N, a = map(int,input().split())
b = set([*map(int,input().split())])
largest = max(list(b))

out = 0

for x in range(1,100):
    if a**x > largest:
        break
    for y in range(1,100):
        if y*a**x in b:
            out += 1
print(out)
