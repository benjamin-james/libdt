#ifndef TEST_H
#define TEST_H

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int test_status = 0;
bool exit_on_failure = false;
#define test_assert(expr, str, ...) {			\
	if (!(expr)) {					\
	        test_status = 1;			\
		printf("Test failure in %s at line %i in %s: ", __FILE__, __LINE__, __func__); \
		printf(str, ##__VA_ARGS__); \
		printf("\n");		    \
		if (exit_on_failure) {	    \
		        exit(EXIT_FAILURE); \
		}			    \
	}				    \
}

#endif
