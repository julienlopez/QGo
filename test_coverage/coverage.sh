#!/bin/bash

dir=`pwd`
root_dir=$(readlink -m ..)

rm *.gcov
#rm ../obj_tests/*

#find out how to compile the tests

lcov --zerocounters --directory $root_dir/obj_tests --directory $dir --no-external
lcov --capture --initial --directory $root_dir/obj_tests --directory $dir --output-file coverage.info --no-external

echo "running tests"
../bin/tests || { exit 1; }
echo "tests done"

echo "running gcov"
gcov ../src/*.cpp -o $root_dir/obj_tests
echo "gcov done"

echo "running lcov"
lcov --capture --directory $root_dir/obj_tests --directory $dir --directory $root_dir/src --output-file coverage.info --no-checksum --no-external
genhtml -o html coverage.info
echo "lcov done"
