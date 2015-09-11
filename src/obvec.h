#ifndef OBVEC_H
#define OBVEC_H

#include <stdlib.h>
#include <obstack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define obstack_chunck_alloc malloc
#define obstack_chunk_free free

#define obvec_t(T) \
	struct { \
		struct obstack ob_stack; \
		T *data; \
		size_t size, alloc; \
	}

#define obvec_init(o) \
	obstack_init((o)->ob_stack)

#define obvec_destroy(o) \
	obstack_free(&(o)->ob_stack, NULL)

#define obvec_raw_list(o) \
	&(o)->ob_stack, (void **)&(o)->data, sizeof *(o)->data, &(o)->size, &(o)->alloc

#define obvec_insert(o, index, element) \
	( obvec_insert_(obvec_raw_list(o), index) ? -1 :\
	  ((o)->data[index] = (element), 0), (o)->size = _max((o)->size, index), 0 )

#define obvec_push(o, element) \
	( obvec_grow_(obvec_raw_list(o)) ? -1 :\
	  ((o)->data[(o)->size++] = (element), 0), 0)

#define obvec_set(o, index, element) \
	( obvec_set_(obvec_raw_list(o), index) ? -1 :\
	  ((o)->data[index] = (element), 0), 0)

#define obvec_remove(o, index) \
	obvec_remove_(obvec_raw_list(o), index)

int obvec_grow_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc);

int obvec_set_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index);

int obvec_insert_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index);

int obvec_remove_(struct obstack *ob_stack, void **data, size_t data_size, size_t *obvec_size, size_t *obvec_alloc, size_t index);

#ifdef __cplusplus
}
#endif

#endif
