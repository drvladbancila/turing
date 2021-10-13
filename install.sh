#!/bin/bash

gcc src/main.c src/checks.c src/errors.c src/input.c src/run.c -o turing
mkdir /usr/bin/turing/
mv turing /usr/bin/turing
cp src/banner /usr/bin/turing
ln -s /usr/bin/turing/turing /bin/turing
