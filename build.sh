#!/bin/sh

find src -name "*.cpp" -execdir gcc -I/home/gremy/git_pub/botsim/include/bullet/src/ -c {} \;
gcc -o botsim $(find src -name "*.o") $(pkg-config --libs openscenegraph) -lm lib/libbulletdynamics.a lib/libbulletcollision.a lib/libbulletmath.a
