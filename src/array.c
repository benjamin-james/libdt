#include "stdlib.h"
#include "string.h"

#include "array.h"

#define START_SIZE 4


struct array *array_create(int size, int (*cmp)(void *, void *))
{
	struct array *a;
	if (size <= 0)
		return NULL;
	a = malloc(sizeof(struct array));
	if (a == NULL)
		return NULL;
	a->buffer = malloc(size * sizeof(void*));
	a->cmp = cmp;
	a->size = 0;
	if (a->buffer == NULL) {
		free(a);
		a = NULL;
	}
	a->alloc = size;
	return a;
}

void array_empty(struct array *a)
{
	a->alloc = 0;
}

void array_destroy(struct array *a)
{
	if (!a)
		return;
	if (a->buffer)
		free(a->buffer);
	free(a);
}

static int binary_search(const struct array *a, void *data)
{
	void *buf = NULL;
	int result = -1, end = a->size, mid = a->size / 2, begin = 0;
	if (!data)
		return -1;
	while (end > 0 && !buf) {
		mid = end / 2;
		result = a->cmp(data, array_get(a, begin + mid));
		if (result > 0) {
			begin += mid + 1;
			end -= mid + 1;
		} else if (result < 0) {
			end = mid;
		} else {
			buf = array_get(a, begin + mid);
			begin += mid;
		}
	}
	if (begin > a->size)
		begin--;
	return begin;
}
void *array_search(const struct array *a, void *data)
{
	int i = binary_search(a, data);
	if (i < 0)
		return NULL;
	return a->buffer[i];
}
void array_add(struct array *a, void *data)
{
	int pos = binary_search(a, data);
	if (pos < 0)
		return;
	if (a->buffer[pos])
		array_set(a, pos, data);
	else
		array_insert(a, pos, data);
}

void array_append(struct array *a, void *data)
{
	if (a->size == a->alloc) {
		if (a->buffer != NULL) {
			a->alloc *= 2;
			a->buffer = realloc(a->buffer, a->alloc * sizeof(void*));
		} else {
			a->buffer = malloc(START_SIZE * sizeof(void*));
			a->alloc = START_SIZE;
		}
	}
	if (a->buffer != NULL) {
		a->buffer[a->size] = data;
		a->size++;
	}
}

void array_push(struct array *a, void * data)
{
	int i;
	void **temp;
	if (a->size == a->alloc) {
		if (a->buffer != NULL) {
			a->alloc *= 2;
			temp = malloc(a->alloc * sizeof(void*));
			if (temp) {
				for (i = 0; i < a->size; i++)
					temp[i + 1] = a->buffer[i];
				free(a->buffer);
				a->buffer = temp;
			}
		} else {
			a->buffer = malloc(START_SIZE * sizeof(void*));
			if (a->buffer)
				a->alloc = START_SIZE;
		}
	} else {
		for (i = a->size; i > 0; i--)
			a->buffer[i] = a->buffer[i - 1];
	}
	if (a->buffer != NULL) {
		a->buffer[0] = data;
		a->size++;
	}
}

void array_insert(struct array *a, int pos, void *data)
{
	void **temp;
	if (pos == 0) {
		array_push(a, data);
	} else if (pos == a->size) {
		array_append(a, data);
	} else if (pos < a->size) {
		int i;
		if (a->size == a->alloc) {
			a->alloc *= 2;
			temp = malloc(a->alloc * sizeof(void*));
			if (temp) {
				memcpy(temp, a->buffer, pos * sizeof(void*));
				memcpy(temp + pos + 1, a->buffer + pos, (a->size - pos) * sizeof(void*));
				free(a->buffer);
				a->buffer = temp;
			}
		} else {
			for (i = a->size - 1; i >= pos; i--)
				a->buffer[i + 1] = a->buffer[i];
		}
		a->buffer[pos] = data;
		a->size++;
	}
}

void *array_remove(struct array *a, int index)
{
	void *data;
	int i;
	if (a->size < index + 1) {
		data = NULL;
	} else if (index == 0) {
		data = a->buffer[0];
		for (i = 1; i < a->size; i++)
			a->buffer[i - 1] = a->buffer[i];
		a->size--;
	} else if (index == a->size - 1) {
		data = a->buffer[index];
		a->size--;
	} else {
		data = a->buffer[index];
		for (i = index; i < a->size - 1; i++)
			a->buffer[i] = a->buffer[i + 1];
		a->size--;
	}
	return data;
}

void *array_get(const struct array *a, int pos)
{
	void *data = NULL;
	if (pos < a->size)
		data = a->buffer[pos];
	return data;
}

void *array_set(struct array *a, int pos, void *data)
{
	if (pos == a->size) {
		array_append(a, data);
		return NULL;
	} else if (pos < a->size) {
		void *temp = a->buffer[pos];
		a->buffer[pos] = data;
		return temp;
	}
	return NULL;
}

void array_set_size(struct array *a, int size)
{
	a->buffer = realloc(a->buffer, size);
	if (a->buffer)  {
		a->alloc = size;
		if (a->alloc < a->size)
			a->size = a->alloc;
	} else {
		a->alloc = 0;
		a->size = 0;
	}
}

int array_get_size(const struct array *a)
{
	if (!a) 
		return 0;
	return a->size;
}
void array_shuffle(struct array *a)
{
	int i,r;
	void *tmp;
	for (i = a->size-1; i >= 0; i--) {
		r = rand() % (i+1);
		if (a->buffer[i] && a->buffer[r]) {
			tmp = a->buffer[i];
			a->buffer[i] = a->buffer[r];
			a->buffer[r] = tmp;
		}
	}
}
struct array *array_copy(struct array *a)
{
	struct array *b = array_create(a->size, a->cmp);
	int i;
	for (i = 0; i < a->size; i++)
		b->buffer[i] = a->buffer[i];
	b->size = a->size;
	return b;
}
static void msort(struct array *a, int begin, int end, struct array *b)
{
	int i,j,k,middle = begin + (end - begin) / 2;
	if (end <= begin) 
		return;
	msort(a,begin,middle,b);
	msort(a,middle+1,end,b);
	for (i = begin; i <= end; i++)
		b->buffer[i] = a->buffer[i];
	for (i = begin, j = middle+1, k = begin; i <= middle && j <= end; k++) {
		if (a->cmp(b->buffer[i],b->buffer[j]) <= 0)
			a->buffer[k] = b->buffer[i++];
		else
			a->buffer[k] = b->buffer[j++];
	}
	for (;i <= middle; i++,k++) 
		a->buffer[k] = b->buffer[i];
}
void array_sort(struct array *a)
{
	struct array *b = array_copy(a);
	msort(a,0,array_get_size(a)-1,b);
	array_destroy(b);
}
