#include <string.h>
#include "array.h"

int _expand(struct dt_array *a, size_t new_alloc)
{
        void **data = a->m_alloc(new_alloc * sizeof(*data));
	if (data == NULL) {
		return -1;
	}
	a->alloc = new_alloc;
	memcpy(data, a->data, a->size * sizeof(*data));
	if (a->data != NULL) {
		a->m_free(a->data);
	}
	a->data = data;
	if (a->deep) {
                for (size_t i = a->size; i < a->alloc; i++) {
			a->data[i] = a->m_alloc(a->item_size);
			if (a->data[i] == NULL) {
				return -1;
			}
		}
	}
	return 0;
}

int dt_array_create(struct dt_array *a, size_t initial_size, size_t item_size, double expand_factor, bool deep, mem_alloc ma, mem_calloc mc, mem_free mf)
{
        if (expand_factor <= 1.0) {
		expand_factor = 2;
	}
	a->alloc = 0;
	a->size = 0;
	a->item_size = item_size;
	a->deep = deep;
	a->m_alloc = ma;
	a->m_calloc = mc;
	a->m_free = mf;
	a->data = NULL;
	_expand(a, initial_size);
	return a->data == NULL ? -1 : 0;
}

int dt_array_destroy(struct dt_array *a)
{
	if (a->deep) {
		for (size_t i = 0; i < a->size; i++) {
			a->m_free(a->data[i]);
		}
	}
	if (a->data != NULL) {
		a->m_free(a->data);
	}
	a->alloc = a->size = 0;
	return 0;
}

void *_set(struct dt_array *a, void *to, void *from)
{
	if (a->deep) {
		if (to == NULL) {
			to = a->m_alloc(a->item_size);
		}
		if (to != NULL) {
			memcpy(to, from, a->item_size);
		}
		return to;
	} else {

		return from;
	}
}

int _grow(struct dt_array *a)
{
	size_t new_alloc = a->alloc * a->expand_factor;
	if (new_alloc <= a->alloc) {
		return -1; // Overflow
	}
	return _expand(a, new_alloc);
}

int dt_array_push(struct dt_array *a, void *data)
{
	if (a->size >= a->alloc) {
		if (_grow(a) < 0) {
			return -1;
		}
	}
	a->data[a->size] = _set(a, a->data[a->size], data);
	a->size++;
	return 0;
}

int dt_array_add(struct dt_array *a, void *data, size_t index)
{
	if (index == a->size) {
		return dt_array_push(a, data);
	} else if ((a->size == 0 && index != 0) || index > (a->size - 1)) {
		return -1;
	}
	if (a->size >= a->alloc) {
		if (_grow(a) < 0) {
			return -1;
		}
	}
	size_t shift = (a->size - index) * sizeof(*a->data);
	memmove(a->data + index + 1, a->data + index, shift);
        a->data[a->size] = _set(a, a->data[a->size], data);
	a->size++;
	return 0;
}

int dt_array_replace(struct dt_array *a, void *data, size_t index, void *ret)
{
        if (dt_array_get(a, index, ret) < 0) {
		return -1;
	}
	a->data[index] = _set(a, a->data[index], data);
	return 0;
}

int dt_array_remove(struct dt_array *a, void *data, void *ret)
{
	size_t index;
        if (dt_array_find(a, data, &index) < 0) {
		return -1; //not found
	}
	return dt_array_remove_at(a, index, ret);
}

int dt_array_remove_at(struct dt_array *a, size_t index, void *ret)
{
	if (dt_array_get(a, index, ret) < 0) {
		return -1;
	}
	if (index != a->size - 1) {
		size_t block_size = (a->size - index) * sizeof(*a->data);
		memmove(a->data + index, a->data + index + 1, block_size);
	}
	a->size--;
	return 0;
}

int dt_array_clear(struct dt_array *a)
{
	a->size = 0;
	return 0;
}

int dt_array_pop(struct dt_array *a, void *ret)
{
	return dt_array_remove_at(a, a->size - 1, ret);
}

int dt_array_peek(struct dt_array *a, void *ret)
{
	return dt_array_get(a, a->size - 1, ret);
}

int dt_array_get(struct dt_array *a, size_t index, void *ret)
{
	if (index >= a->size) {
		return -1;
	}
	if (ret == NULL) {
		return 0;
	}
	memcpy(ret, a->data[index], a->item_size);
        return 0;
}

int dt_array_subarray(struct dt_array *a, size_t begin, size_t end, struct dt_array *ret)
{
	if (dt_array_create(ret, 1 + end - begin, a->item_size, a->expand_factor, a->deep, a->m_alloc, a->m_calloc, a->m_free) < 0) {
		return -1;
	}

	if (a->deep) {
		for (size_t i = begin; i < end; i++) {
			dt_array_push(ret, a->data[i]);
		}
	} else {
		ret->size = ret->alloc;
		memcpy(ret->data, a->data + begin, ret->size * sizeof(*ret->data));
	}

	return 0;
}

int dt_array_copy(struct dt_array *a, struct dt_array *ret)
{
	return dt_array_subarray(a, 0, a->size - 1, ret);
}

int _ptr_cmp(const void *left, const void *right)
{
	return (int)(left - right);
}

int dt_array_find(struct dt_array *a, void *data, size_t *index)
{
	return dt_array_find_elt(a, data, index, _ptr_cmp);
}

int dt_array_find_elt(struct dt_array *a, void *data, size_t *index, cmp compare)
{
        int count = 0;
	for (size_t i = 0; i < a->size; i++) {
		if (compare(data, a->data[i]) == 0) {
			count++;
			*index = i;
		}
	}
	return count;
}

size_t dt_array_size(struct dt_array *a)
{
	return a->size;
}

size_t dt_array_capacity(struct dt_array *a)
{
	return a->alloc;
}

int dt_array_sort(struct dt_array *a, cmp compare)
{
        qsort(a->data, a->size, sizeof(*a->data), compare);
	return 0;
}

int dt_array_map(struct dt_array *a, void (*map)(void *data))
{
	for (size_t i = 0; i < a->size; i++) {
		map(a->data[i]);
	}
	return 0;
}

int dt_array_iter_init(struct dt_array_iter *iter, struct dt_array *array)
{
	iter->array = array;
	iter->current = 0;
	return 0;
}

int dt_array_iter_next(struct dt_array_iter *iter, void *ret)
{
	int r = dt_array_get(iter->array, iter->current, ret);
	if (r == 0) {
                iter->current++;
	}
        return r != -1;
}

int dt_array_iter_add(struct dt_array_iter *iter, void *data)
{
	return dt_array_add(iter->array, data, iter->current++);
}

int dt_array_iter_remove(struct dt_array_iter *iter, void *ret)
{
	return dt_array_remove_at(iter->array, iter->current - 1, ret);
}

int dt_array_iter_replace(struct dt_array_iter *iter, void *data, void *ret)
{
	return dt_array_replace(iter->array, data, iter->current - 1, ret);
}

int dt_array_iter_index(struct dt_array_iter *iter, size_t *index)
{
        *index = iter->current - 1;
	return 0;
}
