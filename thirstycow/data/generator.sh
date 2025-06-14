#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution oneliner.py

compile gen_rand.py

MAXN=300000


samplegroup
sample 1
sample 2


group group1 19
limits MAXN=200 MAXA=200
include_group sample
tc small-1 gen_rand N=1 MAXA=200
tc small-2 gen_rand N=10 MAXA=200
tc small-3 gen_rand N=100 MAXA=200
tc small-4 gen_rand N=200 MAXA=200
tc small-5 gen_rand N=200 mode=staircase

group group2 29
limits MAXN=3000
include_group group1
tc medium-1 gen_rand N=10 
tc medium-2 gen_rand N=1000 
tc medium-3 gen_rand N=2000 
tc medium-4 gen_rand N=3000 
tc medium-5 gen_rand N=3000 mode=staircase

group group3 52
include_group group2
tc large-1 gen_rand N=100000 
tc large-2 gen_rand N=200000 
tc large-3 gen_rand N=300000 
tc large-4 gen_rand N=300000 
tc large-5 gen_rand N=300000 mode=staircase
