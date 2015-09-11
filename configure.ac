AC_PREREQ([2.69])
AC_INIT(obvec, 0.2)
AC_CONFIG_SRCDIR([src/obvec.c])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([src/config.h])
AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
LT_INIT
# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h obstack.h])
# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_FREE
AC_TYPE_SIZE_T
AC_CHECK_FUNCS([obstack_init obstack_free obstack_alloc])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
