#ifndef DT_COMMON_H
#define DT_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef void *(*mem_alloc)(size_t size);
typedef void *(*mem_calloc)(size_t blocks, size_t block_size);
typedef void  (*mem_free)(void *data);

typedef int (*cmp)(const void *left, const void *right);
#endif
