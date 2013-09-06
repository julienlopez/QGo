#!/bin/bash

rm *.gcov
#rm ../obj_tests/*

#find out how to compile the tests

lcov --zerocounters --directory ../obj_tests --directory .
lcov --capture --initial --directory ../obj_tests --directory . --output-file coverage.info --no-external

echo "running tests"
../bin/tests
echo "tests done"

echo "running gcov"
gcov ../src/*.cpp -o ../obj_tests
echo "gcov done"

echo "running lcov"
lcov --capture --directory ../obj_tests --directory . --output-file coverage.info --no-checksum
genhtml -o html coverage.info
echo "lcov done"

