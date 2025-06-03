#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


struct sbar
{
	int id;
	char name[32];
};

int main()
{
	struct sbar *ptr, *newptr;

	ptr = calloc(1000, sizeof(struct sbar));
	if (!ptr)
	{
		perror("calloc");
		return 1;
	}

	newptr = reallocarray(ptr, 500, sizeof(struct sbar));
	if (!newptr)
	{
		perror("reallocarray");
		free(ptr);
		return 1;
	}

	printf("Reallocated to 500 elements successfully\n");
	free(newptr);
	return 0;
}