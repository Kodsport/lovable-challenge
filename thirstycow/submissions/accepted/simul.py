#!/usr/bin/python3
n = int(input())
a = [*map(int,input().split())]

out = 0
shift = 0
for x in a:
    if x-shift > 0:
        out += x-shift
        shift += x-shift

print(out)
