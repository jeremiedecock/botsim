# [Botsim.org](http://www.jdhp.org/projects_en.html#botsim)

Copyright (c) 2010,2011,2015 Jeremie DECOCK (http://www.jdhp.org)

## Description

Botsim.org is a robots simulator mainly used to test some evolutionary
algorithms. 

## Compile from sources

Botsim.org requires the [cmake](www.cmake.org) build system to be compiled.

Ensure cmake is installed on your system, then open a unix terminal and type:

```
mkdir build
cd build
cmake ..
ccmake
```

Then select the desired compilation targets and options and press 'c' then 'g'.

```
make
```

## Build documentation

You can use [doxygen](www.doxygen.org) to generate the Botsim API
documentation.

Ensure doxygen is installed on your system and type `doxygen` from the
project's root directory.


## License

Botsim.org is distributed under the [MIT License](http://opensource.org/licenses/MIT).
