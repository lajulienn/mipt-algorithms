#include "quick_sort.h"

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
void quickSort(int l, int r)
{
	int x = a[l];
	int i = l;
	int j = r;
	partition(&i, &j, &x);
	if (i < r)
		quickSort(i, r);

	if (l < j)
		quickSort(l, j);
}

void partition(int *i, int *j, int *x)
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