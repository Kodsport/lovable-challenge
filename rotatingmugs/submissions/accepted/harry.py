#!/usr/bin/python3
from collections import Counter

M = int(input())

dirtoind = {"N":0, "W":1, "S":2, "E":3}

a = [*map(lambda x: dirtoind[x],[*input()])]

if sum(a)%2:
    print(-1)
    exit()

ans = 0

c = Counter(a)

for x in c:
    while c[x] > 6:
        c[x] -= 2
        ans += (4-x)%4

vis = set()
vis.add((c[0],c[1],c[2],c[3]))
BFS = [[c[0],c[1],c[2],c[3],0]]
for n,w,s,e,d in BFS:
    
    if w == s == e == 0:
        ans += d
        break
    
    nxt = [n,w,s,e,d+1]
    for i in range(4):
        for j in range(4):
            nxt[i] -= 1
            nxt[j] -= 1
            if nxt[i] >= 0 and nxt[j] >= 0: 
                nxt[(i+1)%4] += 1
                nxt[(j+1)%4] += 1
                if tuple(nxt[:4]) not in vis:
                    BFS.append(nxt[:])
                    vis.add(tuple(nxt[:4]))
                nxt[(i+1)%4] -= 1
                nxt[(j+1)%4] -= 1
            nxt[i] += 1
            nxt[j] += 1



print(ans)
