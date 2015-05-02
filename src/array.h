#ifndef ARRAY_H
#define ARRAY_H

#ifdef __cplusplus
extern "C" {
#endif

struct array {
	int alloc,size;
	void **buffer;
	int (*cmp)(void *, void *);
};

struct array *array_create(int size, int (*cmp)(void *, void *));
void array_destroy(struct array *a);

void *array_search(const struct array *a, void *data);
void array_add(struct array *a, void *data);

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
void array_sort(struct array *a);

#ifdef __cplusplus
}
#endif

#endif
