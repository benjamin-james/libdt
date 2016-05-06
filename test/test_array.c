#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "libdt/array.h"
#include "test.h"

void test_array_push();
void test_array_add();
void test_array_expand();
void test_array_pop();
void test_array_remove();
void test_array_peek();
void test_array_get();
void test_array_find();
void test_array_sort();
void test_array_iter();

int main(int argc, char **argv)
{
	test_array_push();
	test_array_add();
	test_array_expand();
	test_array_pop();
	test_array_remove();
	test_array_peek();
	test_array_get();
	test_array_find();
	test_array_sort();
	test_array_iter();
	return test_status;
}

void test_array_push()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	test_assert(dt_array_push(&array, &a) == 0,
		    "Failed to push %d to array", a);
	test_assert(dt_array_push(&array, &b) == 0,
		    "Failed to push %d to array", b);
	test_assert(dt_array_push(&array, &c) == 0,
		    "Failed to push %d to array", c);
	test_assert(*(int *)array.data[0] == a, "Array data does not match: %d != %d", *(int *)array.data[0], a);
	test_assert(*(int *)array.data[1] == b, "Array data does not match: %d != %d", *(int *)array.data[1], b);
	test_assert(*(int *)array.data[2] == c, "Array data does not match: %d != %d", *(int *)array.data[2], c);
        dt_array_destroy(&array);
}

void test_array_add()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int val = 120;
	test_assert(dt_array_add(&array, &val, 0) == 0,
		    "Failed to add value to array");
	test_assert(*(int *)array.data[0] == val, "Array data does not match");
	dt_array_destroy(&array);

}

void test_array_expand()
{

	struct dt_array array;
	test_assert(
		dt_array_create(&array, 1, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
	int a = 73;
	int b = 12;
	int c = 43;
	test_assert(dt_array_push(&array, &a) == 0,
		    "Failed to push %d to array", a);
	test_assert(dt_array_push(&array, &b) == 0,
		    "Failed to push %d to array", b);
	test_assert(dt_array_push(&array, &c) == 0,
		    "Failed to push %d to array", c);
	test_assert(*(int *)array.data[0] == a, "Array data does not match: %d != %d", *(int *)array.data[0], a);
	test_assert(*(int *)array.data[1] == b, "Array data does not match: %d != %d", *(int *)array.data[1], b);
	test_assert(*(int *)array.data[2] == c, "Array data does not match: %d != %d", *(int *)array.data[2], c);
        dt_array_destroy(&array);
}

void test_array_pop()
{

}

void test_array_remove()
{

}

void test_array_peek()
{

}

void test_array_get()
{

}

void test_array_find()
{

}

void test_array_sort()
{

}

void test_array_iter()
{

}
