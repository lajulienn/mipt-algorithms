#include <cstdio>
#include <stdlib.h>

void insertion_sort(int n, int a[]);

int main()
{
	int n, i; 
	scanf("%d", &n);
	int * a = (int *)malloc(n * sizeof(int));
	if (!a)
	{
		printf("Error, no memory\n");
		free(a);
		return 0;
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
	}
	insertion_sort(n, a);
	for (i = 0; i < n; ++i)
	{
		printf("%d ", a[i]);
	}
	free(a);
	return 0;
}

void insertion_sort(int n, int a[])
{
	int tmp, i, k;
	for (i = 1; i < n; ++i)
	{
		tmp = a[i];
		k = i;
		while (k > 0)
		{
			if (a[k - 1] > tmp) 
			{
				a[k] = a[k - 1];
				--k;
			}
			else 
			{
				break;
			}
		}
		a[k] = tmp;
	}
}