#include "inttypes.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "array.h"

inline uint64_t rdtsc();
int intcmp(void *v, void *v1);
struct array *randArray(int i);
void freeArray(struct array *a);

int main(int argc, char **argv)
{
	srand(time(0));
	if(argc < 2) {
		printf("Usage: %s \\d\n",argv[0]);
		return -1;
	}
	struct array *a = randArray(atoi(argv[1]));

	uint64_t nano = rdtsc();
	array_sort(a);
	nano = rdtsc() - nano;

	printf("took %" PRIu64 " nanoseconds for array of %d\n",nano,array_get_size(a));
	freeArray(a);
	return 0;
}
inline uint64_t rdtsc()
{
	uint32_t lo, hi;
	__asm__ __volatile__ (
		"xorl %%eax, %%eax\n"
		"cpuid\n"
		"rdtsc\n"
		: "=a" (lo), "=d" (hi)
		:
		: "%ebx", "%ecx" );
    return (uint64_t)hi << 32 | lo;
}
int intcmp(void *a, void *b)
{
	return *(int *)a - *(int *)b;
}
struct array *randArray(int length)
{
	int i;
	struct array *a = array_create(length, intcmp);
	for (i = 0; i < length; i++) {
		int *m = malloc(sizeof(int));
		*m = i;
		array_append(a,m);
	}
	array_shuffle(a);
	return a;
}
void freeArray(struct array *a)
{
	int i;
	for (i = 0; i < array_get_size(a); i++)
		free(a->buffer[i]);
	array_destroy(a);
}
