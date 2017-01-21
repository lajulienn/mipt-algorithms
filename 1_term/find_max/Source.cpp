#include <cstdio>
#include <cstdlib>

int find_max(int *a, unsigned n, unsigned *pos);

int main()
{
	unsigned n, i, pos;
	int max;
	scanf("%u", &n);
	int *a = (int *)malloc(n * sizeof(int));
	if (a = NULL)
	{
		printf("Error\n");
		return 0;
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%d", &a[i]);
	}
	max = find_max(a, n, &pos);
	printf("a[%u]\t%d\n", pos, max);
	free(a);
	return 0;
}

int find_max(int *a, unsigned n, unsigned *pos)
{
	int max = a[0], i = 0;
	*pos = i;
	for (i = 1; i < n; ++i)
	{
		if (a[i] > max)
		{
			max = a[i];
			*pos = i;
		}
	}
	return max;
}