#!/usr/bin/python3

n = int(input())
S = list(map(int,input().split()))

if n == 1:
    print(1)
else:
    x = abs(S[0]-S[1])
    ans = 1
    while x%2 == 0:
        ans *= 2
        x //= 2
    print(ans+1)
