#!/bin/bash

find . | grep --color=never -E "(CMakeFiles)|(\\.cmake$)|(Makefile)|(CMakeCache.txt)|(lib)|(bin)|(include)" | tr "\n" "\0" | xargs -0 rm -rf