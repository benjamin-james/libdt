#include "stdlib.h"
#include "string.h"

#include "array.h"

#define START_SIZE 4

array *array_create(int size)
{
	array *array = malloc(sizeof(array));
	if(array == NULL || size <= 0) return NULL;
	array->buffer = malloc(size * sizeof(void*));
	if(array->buffer == NULL)
	{
		free(array);
		array = NULL;
	}
	array->alloc = size;
	return array;
}

void array_empty(array *array)
{
	array->alloc = 0;
}

void array_destroy(array *array)
{
	if(!array) return;
	if(array->buffer) free(array->buffer);
	free(array);
}

void array_append(array *array, void *data)
{
	if(array->size == array->alloc) 
	{
		if(array->buffer != NULL) 
		{
			array->alloc *= 2;
			array->buffer = realloc(array->buffer, array->alloc * sizeof(void*));
		}
		else 
		{
			array->buffer = malloc(START_SIZE * sizeof(void*));
			array->alloc = START_SIZE;
		}
	}
	if(array->buffer != NULL) 
	{
		array->buffer[array->size] = data;
		array->size++;
	}
}

void array_push(array * array, void * data)
{
	int i;
	if(array->size == array->alloc) 
	{
		if(array->buffer != NULL) 
		{
			array->alloc *= 2;
			void **temp = malloc(array->alloc * sizeof(void*));
			if(temp) 
			{
				for (i = 0; i < array->size; i++) temp[i + 1] = array->buffer[i];
				free(array->buffer);
				array->buffer = temp;
			}
		}
		else 
		{
			array->buffer = malloc(START_SIZE * sizeof(void*));
			if(array->buffer) array->alloc = START_SIZE;
		}
	}
	else for(i = array->size; i > 0; i--) array->buffer[i] = array->buffer[i - 1];
	if(array->buffer != NULL) 
	{
		array->buffer[0] = data;
		array->size++;
	}
}

void *array_peekLast(array *array)
{
	void *data = NULL;
	if(array->size > 0) 
	{
		data = array->buffer[array->size - 1];
		array->size--;
	}
	return data;
}

void *array_peek(array *array)
{
	void *data = NULL;
	if(array->size > 0) 
	{
		int i;
		data = array->buffer[0];
		for (i = 1; i < array->size; i++) array->buffer[i - 1] = array->buffer[i];
		array->size--;
	}
	return data;
}

void array_insert(array *array, int pos, void *data)
{
	if(pos == 0) array_push(array, data);
	else if(pos == array->size) array_append(array, data);
	else if(pos < array->size) 
	{
		int i;
		if (array->size == array->alloc) 
		{
			array->alloc *= 2;
			void **temp = malloc(array->alloc * sizeof(void*));
			if(temp) 
			{
				memcpy(temp, array->buffer, pos * sizeof(void*));
				memcpy(temp + pos + 1, array->buffer + pos, (array->size - pos) * sizeof(void*));
				free(array->buffer);
				array->buffer = temp;
			}
		}
		else for (i = array->size - 1; i >= pos; i--) array->buffer[i + 1] = array->buffer[i];
		array->buffer[pos] = data;
		array->size++;
	}
}

void *array_remove(array *array, int index)
{
	void *data;
	if (array->size < index + 1) data = NULL;
	else if (index == 0) data = array_peek(array);
	else if (index == array->size - 1) data = array_peekLast(array);
	else 
	{
		int i;
		data = array->buffer[index];
		for (i = index; i < array->size - 1; i++) array->buffer[i] = array->buffer[i + 1];
		array->size--;
	}
	return data;
}

void *array_get(const array *array, int pos)
{
	void *data = NULL;
	if (pos < array->size) data = array->buffer[pos];
	return data;
}

void *array_set(array *array, int pos, void *data)
{
	void *temp = NULL;
	if (pos == array->size) array_append(array, data);
	else if (pos < array->size) 
	{
		temp = array->buffer[pos];
		array->buffer[pos] = data;
	}
	return temp;
}

void array_set_size(array *array, int size)
{
	array->buffer = realloc(array->buffer, size);
	if (array->buffer) 
	{
		array->alloc = size;
		if (array->alloc < array->size) array->size = array->alloc;
	}
	else 
	{
		array->alloc = 0;
		array->size = 0;
	}
}

int array_get_size(const array *array)
{
	if(!array) return 0;
	return array->size;
}
