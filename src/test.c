#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

typedef array_define(int) myint_t;

int main(void)
{
	myint_t array;
	memset(&array, 0, sizeof array);
	array_set(&array, 4, 5324);
	array_set(&array, 31, 342);
	int i;
	for (i = 0; i < array.size; i++) {
		printf("array: %d\n", array.data[i]);
	}
	free(array.data);
	return 0;
}
