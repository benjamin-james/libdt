#ifndef ARRAY_H
#define ARRAY_H

struct array {
	int alloc,size;
	void **buffer;
};

struct array *array_create(int size);
void array_destroy(struct array *a);

void *array_get(const struct array *a, int index);
void *array_set(struct array *a, int index, void *data);
void array_insert(struct array *a, int index, void *data);
void *array_remove(struct array *a, int index);

void array_append(struct array *a, void *data);
void array_push(struct array *a, void *data);
void *array_pop(struct array *a);

struct array *array_copy(struct array *a);
void array_empty(struct array *a);
void array_set_size(struct array *a, int size);
int array_get_size(const struct array *a);

void array_shuffle(struct array *a);
void array_sort(struct array *a, int (*cmp)(void *, void *));

#endif
