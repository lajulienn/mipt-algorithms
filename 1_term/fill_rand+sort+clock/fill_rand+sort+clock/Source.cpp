#include <cstdio>
#include <cstdlib>
#include <ctime>

void fill_rand(int *a, int n);
bool is_sorted(int *a, int n);
void insertion_sort(int n, int a[]);

int main()
{
	int n;
	clock_t start, stop;
	int *array = (int *)malloc(sizeof(int));
	while (true)
	{
		scanf("%d", &n);
		if (n > sizeof(array) / sizeof(int))
		{
			array = (int *)realloc(array, n * sizeof(int));
			if (array == NULL)
			{
				printf("Error. No memory\n");
				return 0;
			}
		}
		fill_rand(array, n);
		start = clock();
		insertion_sort(n, array);
		stop = clock();
		printf("%d\n", is_sorted(array, n));
		printf("%.2f\n", (stop - start) / (float)CLOCKS_PER_SEC);
	}
	free(array);
	return 0;
}

void fill_rand(int *a, int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; ++i)
	{
		a[i] = rand();
	}
}
bool is_sorted(int *a, int n)
{
	bool flag = true;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] < a[i - 1])
			flag = false;
	}
	return flag;
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