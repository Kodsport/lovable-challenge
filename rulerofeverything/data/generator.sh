#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution full.cpp

compile gen_rand.py
compile gen_manybig.py
compile gen_evenlysplit.py
compile gen_bighull.py
compile gen_hard.py
compile gen_ones_special1.py

samplegroup
limits maxn=10 maxq=5
sample 1

group group1 2
limits maxn=10 maxq=5
include_group sample
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
tc_manual ../manual-tests/max_small.in
tc_manual ../manual-tests/max_small2.in
tc_manual ../manual-tests/overflow.in
tc_manual ../manual-tests/overflow2.in
tc_manual ../manual-tests/weirdprefbug.in

group group2 13
limits maxn=20 maxq=5
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
tc g2-13 gen_hard n=20 maxb=10
tc g2-14 gen_hard n=20 maxb=100
tc g2-15 gen_hard n=20 maxb=1000

group group3 20
limits maxn=1000 maxq=5
include_group group2
tc_manual ../manual-tests/kill-floaterror.in
tc_manual ../manual-tests/many-slopes.in
tc_manual ../manual-tests/floaterror-4.in
tc_manual ../manual-tests/outofbounds.in
for i in {1..5}
do
    tc g3-$i gen_rand n=1000
done
tc g3-6 gen_manybig n=1000
tc g3-7 gen_manybig n=1000
tc g3-8 gen_manybig n=1000
tc g3-9 gen_evenlysplit n=1000 g=1
tc g3-10 gen_evenlysplit n=1000 g=2
tc g3-11 gen_evenlysplit n=1000 g=3
tc g3-12 gen_bighull n=1000 maxb=100000
tc g3-13 gen_hard n=1000 maxb=10
tc g3-14 gen_hard n=1000 maxb=100
tc g3-15 gen_hard n=1000 maxb=1000
tc g3-16 gen_ones_special1 n=1000 maxb=1
tc g3-17 gen_ones_special1 n=1000 maxb=2
tc g3-18 gen_ones_special1 n=1000 maxb=3
tc g3-19 gen_ones_special1 n=1000 maxb=2 num_twos=20 lo_v=20
tc g3-20 gen_ones_special1 n=1000 maxb=3 num_twos=21 lo_v=20
tc g3-21 gen_ones_special1 n=1000 maxb=3 num_twos=22 lo_v=20


group group4 25
limits maxn=200000 maxq=5
include_group group3
for i in {1..5}
do
    tc g4-$i gen_rand n=200000
done
tc g4-6 gen_manybig n=200000
tc g4-7 gen_manybig n=200000
tc g4-8 gen_manybig n=200000
tc g4-9 gen_evenlysplit n=200000 g=1
tc g4-10 gen_evenlysplit n=200000 g=2
tc g4-11 gen_evenlysplit n=200000 g=3
tc g4-12 gen_bighull n=200000 maxb=100000
tc g4-13 gen_hard n=200000 maxb=10
tc g4-14 gen_hard n=200000 maxb=100
tc g4-15 gen_hard n=200000 maxb=1000
tc g4-16 gen_ones_special1 n=200000 maxb=1
tc g4-17 gen_ones_special1 n=200000 maxb=2
tc g4-18 gen_ones_special1 n=200000 maxb=3
tc g4-19 gen_ones_special1 n=200000 maxb=2 num_twos=14 lo_v=20
tc g4-20 gen_ones_special1 n=200000 maxb=3 num_twos=14 lo_v=20

group group5 20
limits maxn=200000 maxq=1000
include_group group4
for i in {1..5}
do
    tc g5-$i gen_rand n=200000 q=1000
done
tc g5-6 gen_manybig n=200000 q=1000
tc g5-7 gen_manybig n=200000 q=1000
tc g5-8 gen_manybig n=200000 q=1000
tc g5-9 gen_evenlysplit n=200000 g=1 q=1000
tc g5-10 gen_evenlysplit n=200000 g=2 q=1000
tc g5-11 gen_evenlysplit n=200000 g=3 q=1000
tc g5-12 gen_bighull n=200000 maxb=100000 q=1000
tc g5-13 gen_hard n=200000 maxb=10 q=1000
tc g5-14 gen_hard n=200000 maxb=100 q=1000
tc g5-15 gen_hard n=200000 maxb=1000 q=1000
tc g5-16 gen_ones_special1 n=200000 maxb=1 q=1000
tc g5-17 gen_ones_special1 n=200000 maxb=2 q=1000
tc g5-18 gen_ones_special1 n=200000 maxb=3 q=1000
tc g5-19 gen_ones_special1 n=200000 maxb=2 num_twos=14 lo_v=20 q=1000
tc g5-20 gen_ones_special1 n=200000 maxb=3 num_twos=14 lo_v=20 q=1000

group group6 20
limits maxn=200000 maxq=200000
include_group group5
for i in {1..5}
do
    tc g6-$i gen_rand n=200000 q=200000
done
tc g6-6 gen_manybig n=200000 q=200000
tc g6-7 gen_manybig n=200000 q=200000
tc g6-8 gen_manybig n=200000 q=200000
tc g6-9 gen_evenlysplit n=200000 g=1 q=200000
tc g6-10 gen_evenlysplit n=200000 g=2 q=200000
tc g6-11 gen_evenlysplit n=200000 g=3 q=200000
tc g6-12 gen_bighull n=200000 maxb=100000 q=200000
tc g6-13 gen_hard n=200000 maxb=10 q=200000
tc g6-14 gen_hard n=200000 maxb=100 q=200000
tc g6-15 gen_hard n=200000 maxb=1000 q=200000
tc g6-16 gen_ones_special1 n=200000 maxb=1 q=200000
tc g6-17 gen_ones_special1 n=200000 maxb=2 q=200000
tc g6-18 gen_ones_special1 n=200000 maxb=3 q=200000
tc g6-19 gen_ones_special1 n=200000 maxb=2 num_twos=14 lo_v=20 q=200000
tc g6-20 gen_ones_special1 n=200000 maxb=3 num_twos=14 lo_v=20 q=200000
