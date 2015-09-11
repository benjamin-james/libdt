#include "obvec.h"

#ifdef HAS_CONFIG_H
#include "config.h"
#endif

/**
 * @brief Expands the array if needed
 */
int obvec_grow_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc)
{
	while (*obvec_size >= *obvec_alloc) {
		void *temp = obstack_alloc(ob_stack, data_size);
		if (temp == NULL)
			return -1;
		data[data_size] = temp;
		(*obvec_alloc)++;
	}
	return 0;
}

/**
 * @brief Allocates enough space so that data can be accessed at index
 */
int obvec_set_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index)
{
	*obvec_size = _max(index, *obvec_size);
	obvec_grow_(ob_stack, data, data_size, obvec_size, obvec_alloc);
	return 0;
}

/**
 * @brief Moves elements above index up so that data can be inserted
 */
int obvec_insert_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index)
{
	return 0;
}

/**
 * @brief Removes data at the index
 *
 * If the data is at the top of the obstack, it is popped off.
 * Otherwise, it is zeroed out.
 */
int obvec_remove_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index)
{
	if (index == *obvec_size) {
		obstack_free(ob_stack, data[index]);
		*obvec_size--;
	} else
		memset(data[index], 0, data_size);
	return 0;
}
