#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>


int main()
{
	printf("Platform pointer size: %zu bytes\n\n", sizeof(void *));

	int xa = 1 << 30;
	int xb = 4;

	int num = xa * xb;

	printf("xa = %d, xb = %d\n", xa, xb);
	printf("num = xa * xb = %d (0x%x)\n", num, num);

	if (num < 0)
	{
		printf("Warning: signed integer overflow occurred. num is negative!\n");
	}

	void *ptr = malloc(num);
	if (!ptr)
	{
		fprintf(stderr, "malloc(%d) failed: %s\n", num, strerror(errno));
	}
	else
	{
		printf("malloc(%d) succeeded. Memory allocated.\n", num);
		free(ptr);
	}

	void *neg_ptr = malloc(-100);
	if (!neg_ptr)
	{
		fprintf(stderr, "malloc(-100) failed as expected: %s\n", strerror(errno));
	} else
	{
		printf("malloc(-100) succeeded (unexpected!)\n");
		free(neg_ptr);
	}

	return 0;
}