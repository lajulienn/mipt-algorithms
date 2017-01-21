#include <cstdio>
#include <ctime>
#include <cstdlib>
#include "Merge_Sort.h"

int main() {
	while (true) {
		int N;
		printf("Enter array size:\n");
		scanf("%d", &N);
		if (N < 0) {
			printf("Enter another number\n");
			continue;
		}
		clock_t start, stop;
		srand(time(NULL));
		int *array = (int *)malloc(N * sizeof(int));

		for (int i = 0; i < N; ++i)
			array[i] = rand();
		//for (int i = 0; i < N; ++i)
			//printf("%d ", array[i]);
		start = clock();
		MergeSort(array, N);
		stop = clock();
		double unique = CountUnique(array, N);
		printf("*rand\nuniqueness = %.1f%%\n", unique * 100);
		printf("IsSorted = %d\n", IsSorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);
		//for (int i = 0; i < N; ++i)
			//printf("%d ", array[i]);
		//printf("\n");

		for (int i = 0; i < N; ++i)
			array[i] = i;
		start = clock();
		MergeSort(array, N);
		stop = clock();
		unique = CountUnique(array, N);
		printf("*sorted\nuniqueness = %.1f%%\n", unique * 100);
		printf("IsSorted = %d\n", IsSorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		for (int i = 0; i < N; ++i)
			array[i] = N - i;
		start = clock();
		MergeSort(array, N);
		stop = clock();
		unique = CountUnique(array, N);
		printf("*reverse sorted\nuniqueness = %.1f%%\n", unique * 100);
		printf("IsSorted = %d\n", IsSorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);


		for (int i = 0; i < N; ++i)
			array[i] = 5;
		start = clock();
		MergeSort(array, N);
		stop = clock();
		unique = CountUnique(array, N);
		printf("*fill const\nuniqueness = %.1f%%\n", unique * 100);
		printf("IsSorted = %d\n", IsSorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		free(array);
	}
	return 0;
}
