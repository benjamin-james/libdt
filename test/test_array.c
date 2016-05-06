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
void test_array_iter();

int int_cmp(const void *left, const void *right);
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
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
        int pa, pb, pc;
	test_assert(dt_array_pop(&array, &pc) == 0, "Array could not pop off value");
	test_assert(dt_array_pop(&array, &pb) == 0, "Array could not pop off value");
	test_assert(dt_array_pop(&array, &pa) == 0, "Array could not pop off value");
	test_assert(a == pa, "Array data does not match: %d != %d", a, pa);
	test_assert(b == pb, "Array data does not match: %d != %d", b, pb);
	test_assert(c == pc, "Array data does not match: %d != %d", c, pc);
        dt_array_destroy(&array);
}

void test_array_remove()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
        int val;
	test_assert(dt_array_remove_at(&array, 1, &val) == 0, "Array could not remove index 1");
	test_assert(b == val, "Array element removed was not the correct element: %d != %d", b, val);
	test_assert(array.size == 2, "Array size is not correct");
	test_assert(*(int *)array.data[0] == a, "Array element was tampered");
	dt_array_destroy(&array);
}

void test_array_peek()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
        int val;
	test_assert(dt_array_peek(&array, &val) == 0, "Could not peek at last index");
	test_assert(c == val, "Value peeked is not at the end of the array: %d != %d", c, val);
	test_assert(array.size == 3, "Array size is not correct");
	dt_array_destroy(&array);
}

void test_array_get()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
        int val;
	test_assert(dt_array_get(&array, 1, &val) == 0, "Could not get the value at index 1");
	test_assert(b == val, "Value queried is not the correct element: %d != %d", b, val);
	test_assert(array.size == 3, "Array size is not correct");
	dt_array_destroy(&array);
}

void test_array_find()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
        int val = b;
	size_t index;
        test_assert(dt_array_find_elt(&array, &val, &index, int_cmp) == 1, "The amount of values found does not correspond to the actual number");
        test_assert(index == 1, "Index is not correct: %lu != %d", index, 1);
	test_assert(array.size == 3, "Array size is not correct");
	dt_array_destroy(&array);
}

void test_array_iter()
{
	struct dt_array array;
	test_assert(
		dt_array_create(&array, 10, sizeof(int), 2, 0, malloc, calloc, free) == 0,
		"Failed to create array");
        int a = 73;
	int b = 12;
	int c = 43;
	dt_array_push(&array, &a);
	dt_array_push(&array, &b);
	dt_array_push(&array, &c);
	struct dt_array_iter it;
	int val, index = 0;
	for (dt_array_iter_init(&it, &array); dt_array_iter_next(&it, &val); index++) {
		if (index == 0) {
			test_assert(val == a, "Iterator at position %d should be %d, but is actually %d", index, a, val);
		} else if (index == 1) {
                        test_assert(val == b, "Iterator at position %d should be %d, but is actually %d", index, b, val);
		} else if (index == 2) {
			test_assert(val == c, "Iterator at position %d should be %d, but is actually %d", index, c, val);
		}
	}
	test_assert(array.size == 3, "Array size is not correct");
	dt_array_destroy(&array);
}

int int_cmp(const void *left, const void *right)
{
	int *lp = (int *)left;
	int *rp = (int *)right;
	printf("%p and %p\t", lp, rp);
	int l = *(const int *) left;
        int r = *(const int *) right;
	printf("%d vs %d ", l, r);

	if (l > r) {
                puts(">");
		return 1;
	} else if (l < r) {
		puts("<");
		return -1;
	} else {
		puts("=");
		return 0;
	}
}
