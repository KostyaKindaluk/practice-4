#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>


#define SIZE (100 * 1024 * 1024)

void sequential_access(int *arr, size_t size)
{
	volatile long long unsigned int sum = 0;
	for (size_t i = 0; i < size; ++i)
	{
		sum += arr[i];
	}
	printf("Sequential sum: %llu\n", sum);
}

void random_access(int *arr, size_t size, int *indices)
{
	volatile long long unsigned int sum = 0;
	for (size_t i = 0; i < size; ++i)
	{
		sum += arr[indices[i]];
	}
	printf("Random sum: %llu\n", sum);
}

int main()
{
	int *array = malloc(sizeof(int) * SIZE);
	int *indices = malloc(sizeof(int) * SIZE);
	if (!array || !indices)
	{
		perror("malloc");
		return 1;
	}

	for (size_t i = 0; i < SIZE; ++i)
	{
		array[i] = i;
		indices[i] = i;
	}

	for (size_t i = SIZE - 1; i > 0; --i)
	{
		size_t j = rand() % (i + 1);
		int tmp = indices[i];
		indices[i] = indices[j];
		indices[j] = tmp;
	}

	clock_t start, end;

	start = clock();
	sequential_access(array, SIZE);
	end = clock();
	printf("Sequential time: %.3f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

	start = clock();
	random_access(array, SIZE, indices);
	end = clock();
	printf("Random time: %.3f sec\n", (double)(end - start) / CLOCKS_PER_SEC);

	free(array);
	free(indices);
	return 0;
}