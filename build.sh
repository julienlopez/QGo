#!/bin/bash

QMAKE=qmake

$QMAKE "COVERAGE=1" && make VERBOSE=1
