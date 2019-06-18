#!/bin/bash

find . | grep --color=never -E "(CMakeFiles)|(\\.cmake$)|(Makefile)|(CMakeCache.txt)|(lib)|(bin)" | tr "\n" "\0" | xargs -0 rm -rf