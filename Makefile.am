AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = -I m4

AM_CFLAGS = -Wall --std=c99 -I./libdt

lib_LTLIBRARIES = libdt.la
nobase_include_HEADERS = libdt/libdt.h libdt/array.h libdt/common.h
libdt_la_SOURCES = libdt/array.c
libdt_la_LDFLAGS = -version-info 0:2

check_PROGRAMS = test_array

TESTS = test_array

test_array_CFLAGS = -DDEBUG -g -O0
test_array_LDADD = libdt.la
test_array_SOURCES = test/test_array.c test/test.h -I./libdt
