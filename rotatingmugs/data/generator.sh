#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution harry.py

compile gen_rand.py

MAXM=500000


samplegroup
sample 1
sample 2
sample 3

group group1 15
limits onlytwo=1
#tc 2
tc onlytwo-1 gen_rand M=2 mode="onlytwo" a="NE"
tc onlytwo-2 gen_rand M=2 mode="onlytwo" a="EN"
tc onlytwo-3 gen_rand M=2 mode="onlytwo" a="EE"
tc onlytwo-4 gen_rand M=2 mode="onlytwo" a="NN"
tc onlytwo-5 gen_rand M=13 mode="onlytwo"
tc onlytwo-6 gen_rand M=100 mode="onlytwo"
tc onlytwo-7 gen_rand M=100 mode="onlytwo"
tc onlytwo-8 gen_rand M=$MAXM mode="onlytwo" 

group group2 25
limits MAXM=100
tc 1
tc 2
tc 3
tc onlytwo-1
tc onlytwo-2
tc onlytwo-3
tc onlytwo-4
tc onlytwo-5
tc onlytwo-6
tc onlytwo-7
tc small-01 gen_rand M=2 a="NS"
tc small-02 gen_rand M=2 a="NW"
tc small-03 gen_rand M=2 a="WE"
#tc small-04 gen_rand M=2 a="WW"
tc small-05 gen_rand M=2 a="WS"
tc small-06 gen_rand M=2 a="SE"
tc small-07 gen_rand M=2 a="SS"
tc small-08 gen_rand M=3 a="ESW" 
tc small-09 gen_rand M=3 a="EES" 
tc small-10 gen_rand M=4 a="WEEE" 
tc small-11 gen_rand M=5 
tc small-12 gen_rand M=5 a="NNWSE"
tc small-13 gen_rand M=4 a="NWSE"
tc small-14 gen_rand M=6 
tc small-15 gen_rand M=20
tc small-16 gen_rand M=79
tc small-17 gen_rand M=100
tc small-18 gen_rand M=100 
tc small-19 gen_rand M=100 w=99 e=1
tc small-20 gen_rand M=100 w=13 e=29 s=58
tc small-21 gen_rand M=100 n=96 w=1 e=3
tc small-22 gen_rand M=100 w=1 e=99
tc small-23 gen_rand M=99 s=1 e=98
tc small-24 gen_rand M=99 s=1 w=1 e=97
tc small-25 gen_rand M=100 w=7 e=93
tc small-26 gen_rand M=100 s=10 w=13 e=77
tc small-27 gen_rand M=99 n=2 s=1 e=96
tc small-28 gen_rand M=100 n=3 s=1 e=96
tc small-29 gen_rand M=3 a="NEW"
tc small-30 gen_rand M=100 n=98 e=1 w=1

group group3 60
include_group group1
include_group group2
tc large-01 gen_rand M=1000 
tc large-02 gen_rand M=30000
tc large-03 gen_rand M=$MAXM
tc large-04 gen_rand M=300000 w=1 e=299999
tc large-05 gen_rand M=300001 s=1 e=300000
tc large-06 gen_rand M=300001 s=1 w=1 e=299997
tc large-07 gen_rand M=400004 w=100001 e=300003
tc large-08 gen_rand M=500000 s=10001 w=20001 e=469998
tc large-09 gen_rand M=$MAXM n=$(($MAXM-2)) e=1 w=1
