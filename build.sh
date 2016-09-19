#!/bin/bash

QMAKE=qmake

$QMAKE -v
$QMAKE "COVERAGE=1" && make VERBOSE=1
