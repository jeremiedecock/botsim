#!/bin/sh

find src -name "*.cpp" -execdir gcc -I/home/gremy/git_pub/botsim/include/bullet/src/ -c {} \;
find src -name "*.o"
