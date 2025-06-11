#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution nils_deterministic.cpp

compile gen_rand.py

MAXN=500000
MAXS=1000000000

samplegroup
sample 1
sample 2

group group1 15
limits maxn=2
tc 2
tc two-1 gen_rand n=2
tc two-2 gen_rand n=2
tc two-3 gen_rand n=2
tc two-4 gen_rand n=2
tc two-5 gen_rand n=2
tc one-1 gen_rand n=1
tc two-fix-1 gen_rand mode=two  x=1025
tc two-fix-2 gen_rand mode=two  x=536870913
tc two-fix-3 gen_rand mode=two  x=570425345
tc two-fix-4 gen_rand mode=two  x=805306369
tc two-fix-5 gen_rand mode=two  x=409993217
tc two-fix-6 gen_rand mode=two  x=939524097
tc two-fix-7 gen_rand mode=two  x=209226753
tc two-fix-8 gen_rand mode=two  x=800000009
tc two-fix-9 gen_rand mode=two  x=999999999
tc two-fix-10 gen_rand mode=two x=1000000000
tc two-fix-11 gen_rand mode=two  x=32769 shift=32769
tc two-fix-12 gen_rand mode=two x=262145 shift=10

group group2 30
limits maxn=100 maxs=1000000
tc 1
tc small-1 gen_rand n=100 s=1000000
tc small-2 gen_rand n=100 s=1000000
tc small-3 gen_rand n=100 s=1000000
tc small-4 gen_rand n=100 s=1000000
tc small-5 gen_rand n=100 s=1000000
tc small-biganswer-1 gen_rand n=100 s=1000000 p=5 mode=power
tc small-biganswer-2 gen_rand n=100 s=1000000 p=10 mode=power
tc small-biganswer-3 gen_rand n=100 s=1000000 p=15 mode=power
tc small-biganswer-4 gen_rand n=100 s=1000000 p=18 mode=power
tc small-biganswer-5 gen_rand n=100 s=1000000 p=18 mode=power
tc small-odd gen_rand n=99 s=1000000
tc small-ap-1 gen_rand n=32 s=1000000 d=16384 mode=ap
tc small-ap-2 gen_rand n=4 s=1000000 d=262144 mode=ap
tc small-rec-1 gen_rand n=100 s=1000000 mode=recursive
tc small-rec-2 gen_rand n=100 s=1000000 mode=recursive
tc small-rec-3 gen_rand n=100 s=1000000 mode=recursive
tc small-rec-4 gen_rand n=100 s=1000000 mode=recursive
tc two-fix-11
tc two-fix-12

group group3 55
include_group group1
include_group group2
tc large-1 gen_rand n=$MAXN s=$MAXS
tc large-2 gen_rand n=$MAXN s=$MAXS
tc large-3 gen_rand n=$MAXN s=$MAXS
tc large-4 gen_rand n=$MAXN s=$MAXS
tc large-5 gen_rand n=$MAXN s=$MAXS
tc large-6 gen_rand n=$MAXN s=$MAXS
tc large-biganswer-1 gen_rand n=$MAXN s=$MAXS p=10 mode=power
tc large-biganswer-2 gen_rand n=$MAXN s=$MAXS p=16 mode=power
tc large-biganswer-3 gen_rand n=$MAXN s=$MAXS p=20 mode=power
tc large-biganswer-4 gen_rand n=$MAXN s=$MAXS p=28 mode=power
tc large-biganswer-5 gen_rand n=$MAXN s=$MAXS p=28 mode=power
tc large-odd gen_rand n=$(($MAXN-1)) s=$MAXS
tc large-ap-1 gen_rand n=4 s=$MAXS d=268435456 mode=ap
tc large-ap-2 gen_rand n=8 s=$MAXS d=134217728 mode=ap
tc large-ap-3 gen_rand n=28 s=$MAXS d=33554432 mode=ap
tc large-rec-1 gen_rand n=$MAXN s=$MAXS mode=recursive
tc large-rec-2 gen_rand n=$MAXN s=$MAXS mode=recursive
tc large-rec-3 gen_rand n=$MAXN s=$MAXS mode=recursive
tc large-rec-4 gen_rand n=$MAXN s=$MAXS mode=recursive
tc large-rec-5 gen_rand n=$MAXN s=$MAXS mode=recursive
tc large-rec-6 gen_rand n=$MAXN s=$MAXS mode=recursive
