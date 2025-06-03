#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


int main()
{
	size_t initial_size = 1024 * 1024;
	size_t max_size = (size_t)-1;
	void *ptr = malloc(initial_size);

	if (!ptr)
	{
		perror("Initial malloc failed");
		return 1;
	}

	printf("Initial malloc succeeded: %zu bytes\n", initial_size);

	void *tmp = realloc(ptr, max_size);
	if (!tmp)
	{
		fprintf(stderr, "realloc failed to allocate %zu bytes: %s\n", max_size, strerror(errno));
		printf("Original pointer is still valid: %p\n", ptr);
		free(ptr);
	}
	else
	{
		printf("realloc unexpectedly succeeded: %p\n", tmp);
		free(tmp);
	}

	return 0;
}