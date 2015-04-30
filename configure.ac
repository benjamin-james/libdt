#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT(array, 1.0)
AC_CONFIG_SRCDIR([src/array.c])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
LT_INIT
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([free memcpy rand])

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
