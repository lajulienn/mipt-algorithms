#include "q_sort.h"
#include <cstdlib>

int urand()
{
	int result;
	char *tmp = (char *)&result;
	for (int i = 0; i < sizeof(int); ++i)
		tmp[i] = rand();
	result = *(int*)tmp;
	return result;
}

double count_unique(int *a, int n)
{
	unsigned count = 1;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] != a[i - 1])
			++count;
	}
	return (double)count / n;
}
bool is_sorted(int *array, int size) {
	for (int i = 1; i < size; ++i)
		if (array[i] < array[i - 1])
			return false;
	return true;
}