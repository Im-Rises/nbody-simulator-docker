#!/bin/sh

cmake .
make
./NBodyCalculator $1 $2 $3