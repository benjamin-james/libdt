#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"


int main(int argc, char **argv)
{
	bool deep = argc > 1;
        struct dt_array array;
	dt_array_create(&array, 10, sizeof(int), 2, deep, malloc, calloc, free);

	int a = 5;
	int b = 7;
	int c = 32;
	int d = 10;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
	dt_array_push(&array, &d);

	a = 666;

	printf("\n");

	struct dt_array_iter it;
	int val;
	for (dt_array_iter_init(&it, &array); dt_array_iter_next(&it, &val);) {
		printf("%d\n", val);
	}

	dt_array_destroy(&array);
	return 0;
}
