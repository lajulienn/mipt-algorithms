#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "q_sort.h"

//const int N = 3000;
void swap(int *a, int *b);
void quickSort(int *a, int l, int r);
void partition(int *a, int *i, int *j, int *x);

int main()
{
	while (true) {
		int N;
		scanf("%d", &N);
		clock_t start, stop;
		srand(time(NULL));
		int *array = (int *)malloc(N * sizeof(int));
		for (int i = 0; i < N; ++i) {
			array[i] = rand();
		}
		double unique = count_unique(array, N);
		printf("*rand\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		quickSort(array, 0, N - 1);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		for (int i = 0; i < N; ++i)
			array[i] = i;
		unique = count_unique(array, N);
		printf("*sorted\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		quickSort(array, 0, N - 1);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		for (int i = 0; i < N; ++i)
			array[i] = N - i;
		unique = count_unique(array, N);
		printf("*reverse sorted\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		quickSort(array, 0, N - 1);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);


		for (int i = 0; i < N; ++i)
			array[i] = 5;
		unique = count_unique(array, N);
		printf("*fill const\nuniqueness = %.1f%%\n", unique * 100);
		start = clock();
		quickSort(array, 0, N - 1);
		stop = clock();
		printf("is_sorted = %d\n", is_sorted(array, N));
		printf("time = %.8f\n\n", (double)(stop - start) / (double)CLOCKS_PER_SEC);

		free(array);
	}
	return 0;
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void quickSort(int *a, int l, int r)
{
	int x = a[l];
	int i = l;
	int j = r;
	partition(a, &i, &j, &x);
	if (i < r)
		quickSort(a, i, r);

	if (l < j)
		quickSort(a ,l, j);
}

void partition(int *a, int *i, int *j, int *x)
{
	while (*i <= *j)
	{
		while (a[*i] < *x) (*i)++;
		while (a[*j] > *x) (*j)--;
		if (*i <= *j)
		{
			swap(&a[*i], &a[*j]);
			(*i)++;
			(*j)--;
		}
	}
}