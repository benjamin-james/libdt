#include "stdlib.h"
#include "string.h"

#include "array.h"

#define START_SIZE 4

array *array_copy(array *a)
{
	array *b = array_create(a->size);
	int i;
	for(i = 0; i < a->size; i++)
	{
		b->buffer[i] = a->buffer[i];
	}
	b->size = a->size;
	return b;
}
void msort(array *a, int begin, int end, int (*cmp)(void *, void *), array *b)
{
	if(end <= begin) return;
	int i,j,k,middle = begin + (end - begin) / 2;
	msort(a,begin,middle,cmp,b);
	msort(a,middle+1,end,cmp,b);
	for(i = begin; i <= end; i++) b->buffer[i] = a->buffer[i];
	for(i = begin, j = middle+1, k = begin; i <= middle && j <= end; k++)
	{
		if(cmp(b->buffer[i],b->buffer[j]) <= 0) a->buffer[k] = b->buffer[i++];
		else a->buffer[k] = b->buffer[j++];
	}
	for(;i <= middle; i++,k++) a->buffer[k] = b->buffer[i];
}
void array_sort(array *a, int (*cmp)(void *, void *))
{
	array *b = array_copy(a);
	msort(a,0,array_get_size(a)-1,cmp,b);
	array_destroy(b);
}
array *array_create(int size)
{
	array *a = malloc(sizeof(array));
	if(a == NULL || size <= 0) return NULL;
	a->buffer = malloc(size * sizeof(void*));
	a->size = 0;
	if(a->buffer == NULL)
	{
		free(a);
		a = NULL;
	}
	a->alloc = size;
	return a;
}

void array_empty(array *a)
{
	a->alloc = 0;
}

void array_destroy(array *a)
{
	if(!a) return;
	if(a->buffer) free(a->buffer);
	free(a);
}

void array_append(array *a, void *data)
{
	if(a->size == a->alloc) 
	{
		if(a->buffer != NULL) 
		{
			a->alloc *= 2;
			a->buffer = realloc(a->buffer, a->alloc * sizeof(void*));
		}
		else 
		{
			a->buffer = malloc(START_SIZE * sizeof(void*));
			a->alloc = START_SIZE;
		}
	}
	if(a->buffer != NULL) 
	{
		a->buffer[a->size] = data;
		a->size++;
	}
}

void array_push(array *a, void * data)
{
	int i;
	if(a->size == a->alloc) 
	{
		if(a->buffer != NULL) 
		{
			a->alloc *= 2;
			void **temp = malloc(a->alloc * sizeof(void*));
			if(temp) 
			{
				for (i = 0; i < a->size; i++) temp[i + 1] = a->buffer[i];
				free(a->buffer);
				a->buffer = temp;
			}
		}
		else 
		{
			a->buffer = malloc(START_SIZE * sizeof(void*));
			if(a->buffer) a->alloc = START_SIZE;
		}
	}
	else for(i = a->size; i > 0; i--) a->buffer[i] = a->buffer[i - 1];
	if(a->buffer != NULL) 
	{
		a->buffer[0] = data;
		a->size++;
	}
}

void *array_peekLast(array *a)
{
	void *data = NULL;
	if(a->size > 0) 
	{
		data = a->buffer[a->size - 1];
		a->size--;
	}
	return data;
}

void *array_peek(array *a)
{
	void *data = NULL;
	if(a->size > 0) 
	{
		int i;
		data = a->buffer[0];
		for (i = 1; i < a->size; i++) a->buffer[i - 1] = a->buffer[i];
		a->size--;
	}
	return data;
}

void array_insert(array *a, int pos, void *data)
{
	if(pos == 0) array_push(a, data);
	else if(pos == a->size) array_append(a, data);
	else if(pos < a->size) 
	{
		int i;
		if (a->size == a->alloc) 
		{
			a->alloc *= 2;
			void **temp = malloc(a->alloc * sizeof(void*));
			if(temp) 
			{
				memcpy(temp, a->buffer, pos * sizeof(void*));
				memcpy(temp + pos + 1, a->buffer + pos, (a->size - pos) * sizeof(void*));
				free(a->buffer);
				a->buffer = temp;
			}
		}
		else for (i = a->size - 1; i >= pos; i--) a->buffer[i + 1] = a->buffer[i];
		a->buffer[pos] = data;
		a->size++;
	}
}

void *array_remove(array *a, int index)
{
	void *data;
	if (a->size < index + 1) data = NULL;
	else if (index == 0) data = array_peek(a);
	else if (index == a->size - 1) data = array_peekLast(a);
	else 
	{
		int i;
		data = a->buffer[index];
		for (i = index; i < a->size - 1; i++) a->buffer[i] = a->buffer[i + 1];
		a->size--;
	}
	return data;
}

void *array_get(const array *a, int pos)
{
	void *data = NULL;
	if (pos < a->size) data = a->buffer[pos];
	return data;
}

void *array_set(array *a, int pos, void *data)
{
	void *temp = NULL;
	if (pos == a->size) array_append(a, data);
	else if (pos < a->size) 
	{
		temp = a->buffer[pos];
		a->buffer[pos] = data;
	}
	return temp;
}

void array_set_size(array *a, int size)
{
	a->buffer = realloc(a->buffer, size);
	if (a->buffer) 
	{
		a->alloc = size;
		if (a->alloc < a->size) a->size = a->alloc;
	}
	else 
	{
		a->alloc = 0;
		a->size = 0;
	}
}

int array_get_size(const array *a)
{
	if(!a) return 0;
	return a->size;
}
