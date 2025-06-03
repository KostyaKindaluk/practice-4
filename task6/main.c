#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main()
{
	void *ptr = realloc(NULL, 100);
	if (!ptr)
	{
		fprintf(stderr, "realloc(NULL, 100) failed: %s\n", strerror(errno));
	}
	else
	{
		printf("realloc(NULL, 100) succeeded: ptr = %p\n", ptr);
		free(ptr);
	}

	ptr = malloc(50);
	if (!ptr)
	{
		fprintf(stderr, "Initial malloc failed\n");
		return 1;
	}
	memset(ptr, 1, 50);

	void *new_ptr = realloc(ptr, 0);
	if (!new_ptr)
	{
		printf("realloc(ptr, 0) returned NULL (likely freed memory)\n");
	}
	else
	{
		printf("realloc(ptr, 0) returned non-NULL: %p\n", new_ptr);
		free(new_ptr);
	}

	return 0;
}