#include <cstdio>
const int ARRAY_SIZE = 10;
int a[ARRAY_SIZE] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
void swap(int *a, int *b);
void quickSort(int l, int r);
void partition(int *i, int *j, int *x);
#include "quick_sort.h"

int main()
{
	int n = ARRAY_SIZE;
	/*scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
	scanf("%d", &a[i]);
	}*/
	quickSort(0, n - 1);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	return 0;
}