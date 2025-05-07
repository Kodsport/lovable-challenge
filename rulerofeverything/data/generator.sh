#!/usr/bin/env bash

PPATH=$(realpath ..)
. ../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution nlogn.cpp

compile gen_rand.py
compile gen_long.py
compile gen_new.py

samplegroup
limits maxn=10 maxk=10 maxq=10
sample 1

group group1 7
include_group sample
tc_manual ../manual-tests/all.in
tc_manual ../manual-tests/incorrect-ones.in
tc_manual ../manual-tests/kill-feasible.in
tc_manual ../manual-tests/allones.in
for i in {1..20}
do
    tc g1-$i gen_rand n=5
done

group group2 7
include_group sample
include_group group1
for i in {1..20}
do
    tc g2-$i gen_rand n=10
done

group group3 7
include_group sample
include_group group2
for i in {1..20}
do
    tc g3-$i gen_rand n=20
done

group group4 7
include_group sample
include_group group3
for i in {1..20}
do
    tc g4-$i gen_rand n=30
done

group group5 7
include_group sample
include_group group4
for i in {1..20}
do
    tc g5-$i gen_rand n=100
done

group group6 7
include_group sample
include_group group5
for i in {1..20}
do
    tc g6-$i gen_rand n=1000
done

group group7 7
include_group sample
include_group group6
for i in {1..20}
do
    tc g7-$i gen_rand n=100000
done
