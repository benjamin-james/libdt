#ifndef ARRAY_H
#define ARRAY_H

typedef struct 
{
	int alloc,size;
	void **buffer;
} array;

void array_sort(array *a, int (*cmp)(void *, void *));
array *array_create(int size);
array *array_copy(array *a);
void array_empty(array *a);
void array_destroy(array *a);
void array_append(array *a, void *data);
void array_push(array *a, void *data);
void *array_pop(array *a);
void *array_peekLast(array *a);
void *array_peek(array *a);
void array_insert(array *a, int index, void *data);
void *array_remove(array *a, int index);
void *array_get(const array *a, int index);
void *array_set(array *a, int index, void *data);
void array_set_size(array *a, int size);
int array_get_size(const array *a);
#endif 
