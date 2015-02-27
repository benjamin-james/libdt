#include "inttypes.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#include "array.h"

inline uint64_t rdtsc();
int intcmp(void *, void *);
array *randArray(int);
void freeArray(array *);

int main(int argc, char **argv)
{
	srand(time(0));
	if(argc < 2) 
	{
		printf("Usage: %s \\d\n",argv[0]);
		return -1;
	}
	array *a = randArray(atoi(argv[1]));

	uint64_t nano = rdtsc();
	array_sort(a,intcmp);
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
array *randArray(int length)
{
	int i;
	array *a = array_create(length);
	for(i = 0; i < length; i++)
	{
		int *m = malloc(sizeof(int));
		*m = rand();
		array_append(a,m);
	}
	return a;
}
void freeArray(array *a)
{
	int i;
	for(i = 0; i < array_get_size(a); i++) free(a->buffer[i]);
	array_destroy(a);
}
