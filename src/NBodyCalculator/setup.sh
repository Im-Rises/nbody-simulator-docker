#!/bin/sh

cmake -DDOCKER_BUILD=ON .
make
./NBodyCalculator "${1}" "${2}" "${3}"
