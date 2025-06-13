#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution nlogn_opt.cpp

compile gen_rand.py
compile gen_manybig.py
compile gen_evenlysplit.py
compile gen_bighull.py

samplegroup
limits maxn=10
sample 1

group group1 2
limits maxn=10
include_group sample
include_group group1
for i in {1..10}
do
    tc g1-$i gen_rand n=5 maxk=100
done
for i in {11..20}
do
    tc g1-$i gen_rand n=10 maxk=10000
done
tc g1-21 gen_manybig n=10
tc g1-22 gen_manybig n=10
tc g1-23 gen_manybig n=10
tc g1-24 gen_bighull n=10 maxb=100000
tc_manual ../manual-tests/all.in
tc_manual ../manual-tests/incorrect-ones.in
tc_manual ../manual-tests/kill-feasible.in
tc_manual ../manual-tests/allones.in
tc_manual ../manual-tests/floaterror-3.in
tc_manual ../manual-tests/floaterror-5.in
tc_manual ../manual-tests/kill-wronghull.in

group group2 13
limits maxn=20
include_group group1
tc_manual ../manual-tests/floaterror-2.in

for i in {1..5}
do
    tc g2-$i gen_rand n=20
done
tc g2-6 gen_manybig n=20
tc g2-7 gen_manybig n=20
tc g2-8 gen_manybig n=20
tc g2-9 gen_evenlysplit n=20 g=1
tc g2-10 gen_evenlysplit n=20 g=2
tc g2-11 gen_evenlysplit n=20 g=3
tc g2-12 gen_bighull n=20 maxb=100000

group group3 20
limits maxn=100
include_group group2
tc_manual ../manual-tests/kill-floaterror.in
tc_manual ../manual-tests/many-slopes.in
tc_manual ../manual-tests/floaterror-4.in
for i in {1..5}
do
    tc g3-$i gen_rand n=100
done
tc g3-6 gen_manybig n=100
tc g3-7 gen_manybig n=100
tc g3-8 gen_manybig n=100
tc g3-9 gen_evenlysplit n=100 g=1
tc g3-10 gen_evenlysplit n=100 g=2
tc g3-11 gen_evenlysplit n=100 g=3
tc g3-12 gen_bighull n=100 maxb=100000

group group4 25
limits maxn=1000
include_group group3
for i in {1..5}
do
    tc g4-$i gen_rand n=1000
done
tc g4-6 gen_manybig n=1000
tc g4-7 gen_manybig n=1000
tc g4-8 gen_manybig n=1000
tc g4-9 gen_evenlysplit n=1000 g=1
tc g4-10 gen_evenlysplit n=1000 g=2
tc g4-11 gen_evenlysplit n=1000 g=3
tc g4-12 gen_bighull n=1000 maxb=100000

group group5 30
limits maxn=200000
include_group group4
for i in {1..5}
do
    tc g5-$i gen_rand n=200000
done
tc g5-6 gen_manybig n=200000
tc g5-7 gen_manybig n=200000
tc g5-8 gen_manybig n=200000
tc g5-9 gen_evenlysplit n=200000 g=1
tc g5-10 gen_evenlysplit n=200000 g=2
tc g5-11 gen_evenlysplit n=200000 g=3
tc g5-12 gen_bighull n=200000 maxb=100000
