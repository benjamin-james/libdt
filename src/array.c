#include <string.h>
#include "array.h"

static void *__realloc_zero(void *data, size_t old_size, size_t new_size)
{
	void *new_data = realloc(data, new_size);
	if (new_size > old_size && new_data != NULL)
		memset(new_data + old_size, 0, new_size - old_size);
	return new_data;
}
static int __array_realloc(void **data, size_t data_size, size_t *array_size, size_t *array_alloc)
{
	size_t new_alloc = 1;
	if (*array_alloc > 0)
       		new_alloc = 2 * (*array_alloc);
	void *tmp = __realloc_zero(*data, *array_alloc * data_size, new_alloc * data_size);
	if (!tmp)
      		return -1;
	*data = tmp;
	*array_alloc = new_alloc;
	return 0;
}

/**
 * @brief Expands the array as needed
 */
int array_realloc(void **data, size_t data_size, size_t *array_size, size_t *array_alloc, size_t newsize)
{
	int ret = 0;
	while (*array_alloc <= newsize && ret == 0)
		ret = __array_realloc(data, data_size, array_size, array_alloc);
	return ret;
}
