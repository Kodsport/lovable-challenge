#!/usr/bin/python3
import random
print(100000,100663296)
a = [100663296]*50000 + [100663296*random.randint(1,9) for _ in range(50000)] 
print(*a)
