#ifndef ARRAY_H
#define ARRAY_H

typedef struct 
{
	int alloc,size;
	void **buffer;
} array;

void array_sort(array *array, int (*cmp)(void *, void *));
array *array_create(int size);
void array_empty(array *array);
void array_destroy(array *array);
void array_append(array *array, void *data);
void array_push(array *array, void *data);
void *array_peekLast(array *array);
void *array_peek(array *array);
void array_insert(array *array, int index, void *data);
void *array_remove(array *array, int index);
void *array_get(const array *array, int index);
void *array_set(array *array, int index, void *data);
void array_set_size(array *array, int size);
int array_get_size(const array *array);
#endif 
