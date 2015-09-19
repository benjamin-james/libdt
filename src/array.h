#ifndef ARRAY_H
#define ARRAY_H

#include <stdlib.h>

/**
 * @brief Defines an array of type "type"
 */
#define array_define(type) \
	struct { \
		type *data; \
		size_t size, alloc; \
	}

/**
 * @brief Spits out the elements of the struct
 * so that its data can be passed to a function
 */
#define array_raw_list(a) \
        (void **)&(a)->data, sizeof *(a)->data, &(a)->size, &(a)->alloc


/**
 * @brief Sets the element in the index i in array o, expanding the array as necessary.
 *
 *
 * @param a The array to deal with
 * @param index The index to set
 * @param element The new value for element i
 */
#define array_set(a, index, element) \
		  do {		     \
			  if (index >= (a)->alloc) {			\
				  array_realloc(array_raw_list((a)), index+1); \
				  (a)->size = index + 1; \
			  } \
			  (a)->data[index] = element; \
		  } while (0)

int array_realloc(void **data, size_t data_size, size_t *array_size, size_t *array_alloc, size_t newsize);

#endif
