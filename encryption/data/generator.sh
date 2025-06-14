#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_rand.py

MAXN=500000


samplegroup
sample 1
sample 2
sample 3


group group1 40
limits MAXN=100
include_group sample
tc small-1 gen_rand N=1 
tc small-2 gen_rand N=10 
tc small-3 gen_rand N=100 mode=nolv 
tc small-4 gen_rand N=100 mode=nolnov
tc small-5 gen_rand N=100 

group group2 60
include_group group1
tc large-1 gen_rand N=$MAXN mode=nolv
tc large-2 gen_rand N=$MAXN mode=nolnov
tc large-3 gen_rand N=$MAXN mode=nolnov
tc large-4 gen_rand N=$MAXN mode=nolv
tc large-5 gen_rand N=$MAXN

