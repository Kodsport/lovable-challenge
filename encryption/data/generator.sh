#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

#ulimit -s unlimited

use_solution joshua.cpp

compile gen_rand.py

samplegroup
limits maxn=10
sample 1
sample 2

group group1 20
g=1
N=1000
limits maxn=$N
include_group sample
tc g$g-1 gen_rand n=$N k=1
tc g$g-2 gen_rand n=$N k=2
tc g$g-3 gen_rand n=$N k=3
tc g$g-4 gen_rand n=$N
tc g$g-5 gen_rand n=$N
tc g$g-6 gen_rand n=$N mode=repeats s=ab
tc g$g-7 gen_rand n=$N mode=repeats s=abbab
tc g$g-8 gen_rand n=$N mode=long_common_prefix
tc g$g-9 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-10 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-11 gen_rand n=$N mode=interleaved k=4
tc g$g-12 gen_rand n=$N mode=interleaved k=10
tc g$g-13 gen_rand n=$N mode=sparse_matches k=4
tc g$g-14 gen_rand n=$N mode=sparse_matches k=10
tc g$g-15 gen_rand n=$N mode=sparse_matches k=26

group group2 70
g=2
N=100000
limits maxn=$N
include_group group1
tc g$g-1 gen_rand n=$N k=1
tc g$g-2 gen_rand n=$N k=2
tc g$g-3 gen_rand n=$N k=3
tc g$g-4 gen_rand n=$N
tc g$g-5 gen_rand n=$N
tc g$g-6 gen_rand n=$N mode=repeats s=ab
tc g$g-7 gen_rand n=$N mode=repeats s=abbab
tc g$g-8 gen_rand n=$N mode=long_common_prefix
tc g$g-9 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-10 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-11 gen_rand n=$N mode=interleaved k=4
tc g$g-12 gen_rand n=$N mode=interleaved k=10
tc g$g-13 gen_rand n=$N mode=sparse_matches k=4
tc g$g-14 gen_rand n=$N mode=sparse_matches k=10
tc g$g-15 gen_rand n=$N mode=sparse_matches k=26

group group3 10
g=3
N=1000000
limits maxn=$N
include_group group2
tc g$g-1 gen_rand n=$N k=1
tc g$g-2 gen_rand n=$N k=2
tc g$g-3 gen_rand n=$N k=3
tc g$g-4 gen_rand n=$N
tc g$g-5 gen_rand n=$N
tc g$g-6 gen_rand n=$N mode=repeats s=ab
tc g$g-7 gen_rand n=$N mode=repeats s=abbab
tc g$g-8 gen_rand n=$N mode=long_common_prefix
tc g$g-9 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-10 gen_rand n=$N mode=long_common_prefix rev=1
tc g$g-11 gen_rand n=$N mode=interleaved k=4
tc g$g-12 gen_rand n=$N mode=interleaved k=10
tc g$g-13 gen_rand n=$N mode=sparse_matches k=4
tc g$g-14 gen_rand n=$N mode=sparse_matches k=10
tc g$g-15 gen_rand n=$N mode=sparse_matches k=26
