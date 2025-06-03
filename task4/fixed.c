#include <stdio.h>
#include <stdlib.h>


int main()
{
	void *ptr = NULL;
	int n = 16;

	for (int i = 0; i < 3; i++)
	{
		ptr = malloc(n);
		if (!ptr)
		{
			perror("malloc failed");
			return 1;
		}

		printf("Using memory at iteration %d: %p\n", i, ptr);
		free(ptr);
	}

	return 0;
}