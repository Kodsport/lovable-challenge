#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_rand.py

MAXN=200000


samplegroup
sample 1
sample 2
sample 3

group group1 22
limits MAXA=100
include_group sample
tc smallab-1 gen_rand N=1 a=2 MAXA=100
tc smallab-2 gen_rand N=10 a=3 MAXA=100
tc smallab-3 gen_rand N=100 a=24 mode=unique MAXA=100
tc smallab-4 gen_rand N=59 a=7 mode=unique MAXA=100
tc smallab-5 gen_rand N=$MAXN MAXA=100
tc smallab-6 gen_rand N=$MAXN MAXA=100
tc smallab-7 gen_rand N=30 a=2 mode=dense MAXA=100

group group2 33
limits prime=1
tc 1
tc 2
tc smallab-1
tc smallab-2 
tc smallab-4 
tc prime-1 gen_rand N=2 a=2
tc prime-2 gen_rand N=10 a=3 
tc prime-3 gen_rand N=10 prime=1
tc prime-4 gen_rand N=$MAXN prime=1
tc prime-5 gen_rand N=$MAXN a=1597 prime=1 mode=unique
tc prime-6 gen_rand N=$MAXN a=19 prime=1 mode=dense
tc prime-7 gen_rand N=10000 prime=1 MAXA=1000 
tc prime-8 gen_rand N=$MAXN a=2 prime=1 mode=dense
tc prime-9 gen_rand N=$MAXN a=2 prime=1 mode=unique

group group3 45
include_group group1
include_group group2
tc large-1 gen_rand N=10 a=1258
tc large-2 gen_rand N=$MAXN a=99
tc large-3 gen_rand N=$MAXN a=120 mode=unique
tc large-4 gen_rand N=$MAXN a=25 mode=dense
tc large-5 gen_rand N=$MAXN a=108 mode=dense
tc large-6 gen_rand N=$MAXN a=1025 mode=dense
tc large-7 gen_rand N=$MAXN a=1024 mode=dense
