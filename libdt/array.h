#ifndef DT_ARRAY_H
#define DT_ARRAY_H

#include "common.h"

struct dt_array {
	size_t alloc, size;
	double expand_factor;
	void **data;
	bool deep;
	size_t item_size;
	mem_alloc m_alloc;
	mem_calloc m_calloc;
	mem_free m_free;
};

struct dt_array_iter {
	struct dt_array *array;
	size_t current;
};

int dt_array_create(struct dt_array *a, size_t initial_size, size_t item_size, double expand_factor, bool deep, mem_alloc ma, mem_calloc mc, mem_free mf);
int dt_array_destroy(struct dt_array *a);

int dt_array_push(struct dt_array *a, void *data);
int dt_array_add(struct dt_array *a, void *data, size_t index);
int dt_array_replace(struct dt_array *a, void *data, size_t index, void *ret);

int dt_array_remove(struct dt_array *a, void *data, void *ret);
int dt_array_remove_at(struct dt_array *a, size_t index, void *ret);
int dt_array_clear(struct dt_array *a);
int dt_array_pop(struct dt_array *a, void *ret);

int dt_array_peek(struct dt_array *a, void *ret);
int dt_array_get(struct dt_array *a, size_t index, void *ret);

int dt_array_subarray(struct dt_array *a, size_t begin, size_t end, struct dt_array *ret);
int dt_array_copy(struct dt_array *a, struct dt_array *ret);

int dt_array_find(struct dt_array *a, void *data, size_t *index);
int dt_array_find_elt(struct dt_array *a, void *data, size_t *index, cmp compare);

size_t dt_array_size(struct dt_array *a);
size_t dt_array_capacity(struct dt_array *a);


int dt_array_sort(struct dt_array *a, cmp compare);
int dt_array_map(struct dt_array *a, void (*map)(void *data));


int dt_array_iter_init(struct dt_array_iter *iter, struct dt_array *array);
int dt_array_iter_next(struct dt_array_iter *iter, void *ret);

int dt_array_iter_add(struct dt_array_iter *iter, void *data);
int dt_array_iter_remove(struct dt_array_iter *iter, void *ret);

int dt_array_iter_replace(struct dt_array_iter *iter, void *data, void *ret);
int dt_array_iter_index(struct dt_array_iter *iter, size_t *index);

#endif
