#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "sort.h"
#include "heap/heap.h"

//const int N = 1000000;
bool is_sorted(data_t *array, int size) {
	for (int i = 1; i < size; ++i)
		if (array[i] < array[i - 1])
			return false;
	return true;
}
int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		clock_t start, stop;
		srand(time(NULL));
		data_t *array = (data_t *)malloc(N * sizeof(data_t));
		for (int i = 0; i < N; ++i) {
			array[i] = rand();
			//printf("%-12u", array[i]);
			//if ((i + 1) % 4 == 0)
			//	printf("\n");
		}

		double unique = count_unique(array, N);
		printf("*rand\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		heap_sort(array, N);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		/*for (int i = 0; i < N; ++i) {
			printf("%-12u", array[i]);
			if ((i + 1) % 4 == 0)
			printf("\n");
			}*/
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		/*for (int i = 0; i < N; ++i) {
			array[i] = i;
		}
		unique = count_unique(array, N);
		printf("*sorted\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		heap_sort(array, N);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		for (int i = 0; i < N; ++i) {
			array[i] = N - i;
		}
		unique = count_unique(array, N);
		printf("*sorted reverse\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		heap_sort(array, N);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		for (int i = 0; i < N; ++i) {
			array[i] = 1;
		}
		unique = count_unique(array, N);
		printf("*fill const\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		heap_sort(array, N);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);
		free(array);*/
	}
	return 0;
}