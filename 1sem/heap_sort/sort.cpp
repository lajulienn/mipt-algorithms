#include "sort.h"
#include <cstdlib>


void heap_sort(data_t *a, int n)
{
	Heap *heap = heapify(a, n);
	for (int i = 0; i < n; ++i)
	{
		data_t tmp = *(data_top(heap));
		heap_pop(heap);
		a[heap->size] = tmp;
	}
	free(heap);
}

data_t urand()
{
	data_t result;
	char *tmp = (char *)&result;
	for (int i = 0; i < sizeof(data_t); ++i)
		tmp[i] = rand();
	result = *(data_t*)tmp;
	return result;
}

double count_unique(data_t *a, int n)
{
	unsigned count = 1;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] != a[i - 1])
			++count;
	}
	return (double)count / n;
}