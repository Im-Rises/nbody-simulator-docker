#!/bin/sh

cmake -DDOCKER_BUILD=ON .
make
./NBodyCalculator "${1}"
