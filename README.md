# [Botsim.org](http://www.jdhp.org/projects_en.html#botsim)

Copyright (c) 2010,2011,2015 Jeremie DECOCK (http://www.jdhp.org)

## Description

Botsim.org is a robots simulator mainly used to test some evolutionary
algorithms. 

## Source code

Botsim.org source code can be retrieved on [GitHub](https://github.com/jeremiedecock/botsim)
and [JDHP](http://www.jdhp.org/projects_en.html#botsim).

## <a name="sed_dependencies"></a>Dependencies

Botsim.org requires the following libraries to be installed  in your operating
system:

* [Boost::program_options](http://www.boost.org/doc/libs/1_58_0/doc/html/program_options.html) to manage program options;
* [Bullet Physics](http://bulletphysics.org) the open source physics engine used in Botsim.org;
* [Eigen 3](http://eigen.tuxfamily.org) a powerful C++ template library for linear algebra;
* [Open Scene Graph 3.0](http://www.openscenegraph.org/) an open source high performance 3D graphics toolkit.

Debian 8 (Jessie) users should install the following Debian packages to compile
and run Botsim.org:

* libboost-dev;
* libbullet-dev;
* libbullet-extras-dev;
* libeigen3-dev;
* libopenscenegraph-dev;
* build-essential;
* cmake;
* cmake-curses-gui.

Package names are roughly the same in other Debian releases as well as in the other
Debian based systems (Ubuntu, Linux Mint, ...).

## Compile from sources

Botsim.org requires the [cmake](www.cmake.org) build system to compile.

So far, Botsim.org has been tested on Gnu/Linux systems only.
Instructions for Microsoft Windows and MacOS X will come soon.

Ensure *cmake*, *cmake-curses-gui* and
[previously listed dependencies](#sed_dependencies) are
installed on your system. Then open a unix terminal, go to the project's root
directory and type:

```
mkdir build
cd build
cmake ..
ccmake .
```

Then select the desired compilation targets and options then press 'c' and 'g'.

```
make
```

## Build documentation

You can use [doxygen](www.doxygen.org) to generate the Botsim API
documentation.

Ensure doxygen is installed on your system and type `doxygen` from the
Botsim.org project's root directory.


## License

Botsim.org is distributed under the [MIT License](http://opensource.org/licenses/MIT).
