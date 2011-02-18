#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(Botsim, 0.1, gremy@tuxfamily.org)
AM_INIT_AUTOMAKE

AC_CONFIG_SRCDIR([src/main.cpp])
#AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_CPP
AC_PROG_MAKE_SET

# Checks for libraries.
PKG_CHECK_MODULES(LIBBULLET,
                  bullet >= 2.77,
                  [],
                  [AC_MSG_FAILURE([bullet not found])])

PKG_CHECK_MODULES(LIBOSG,
                  openscenegraph >= 2.4.0,
                  [],
                  [AC_MSG_FAILURE([openscenegraph not found])])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([stdlib.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_HEADER_TIME

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday])

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
