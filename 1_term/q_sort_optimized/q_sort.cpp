#include "q_sort.h"
#include <cstdlib>

int Urand() {
	int result;
	char *tmp = (char *)&result;
	for (int i = 0; i < sizeof(int); ++i)
		tmp[i] = rand();
	result = *(int*)tmp;
	return result;
}

double CountUnique(int *a, int n) {
	unsigned count = 1;
	for (int i = 1; i < n; ++i) {
		if (a[i] != a[i - 1])
			++count;
	}
	return (double)count / n;
}
bool IsSorted(int *array, int size) {
	for (int i = 1; i < size; ++i)
		if (array[i] < array[i - 1])
			return false;
	return true;
}
void Swap(int *a, int *b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void QuickSort(int *a, int l, int r) {
	do {
		int i = l;
		int j = r;
		RandomizedPartition(a, &i, &j);
		if (j - l <= r - i) {
			if (l < j)
				QuickSort(a, l, j);
			
			l = i;
			r = r;
		} else {
			if (i < r)
				QuickSort(a, i, r);
			
			l = l;
			r = j;
		}
	} while (l < r);
}

void RandomizedPartition(int *a, int *i, int *j) {
	int pivot = *i + rand() % (*j - *i);
	int x = a[pivot];
	while (*i <= *j) {
		while (a[*i] < x) (*i)++;
		while (a[*j] > x) (*j)--;
		if (*i <= *j) {
			Swap(&a[*i], &a[*j]);
			(*i)++;
			(*j)--;
		}
	}
}