#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>

#define KB_BYTES 1024
#define MB_BYTES (KB_BYTES * 1024)
#define GB_BYTES (MB_BYTES * 1024)


void print_max_size_t()
{
	printf("Current size_t size: %zu bytes\n", sizeof(size_t));
#if INTPTR_MAX == INT64_MAX
	printf("Running on 64-bit architecture\n");
#elif INTPTR_MAX == INT32_MAX
	printf("Running on 32-bit architecture\n");
#else
	printf("Unknown architecture\n");
#endif

	printf("Max size_t value(current): %zu bytes (%.2f GB, %.16f EB)\n",
		(size_t)-1, (double)((size_t)-1) / GB_BYTES, (double)(size_t)-1 / (GB_BYTES) / (1024 * 1024 * 1024));

	uint32_t max_32 = UINT32_MAX;
	printf("Max size_t value on 32-bit: %u bytes (%.2f GB, %.16f EB)\n",
		max_32, (double)max_32 / GB_BYTES, (double)max_32 / (GB_BYTES) / (1024 * 1024 * 1024));

	uint64_t max_64 = UINT64_MAX;
	printf("Max size_t value on 64-bit: %llu bytes (%.2f GB, %.16f EB)\n",
		(unsigned long long)max_64, (double)max_64 / GB_BYTES, (double)max_64 / (GB_BYTES) / (1024 * 1024 * 1024));
}

int main()
{
	printf("malloc size and max value on current, 32-bit and 64-bit architecture:\n");
	print_max_size_t();

	return 0;
}