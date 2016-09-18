#include <cstdio>
#include <cstdlib>

void reverse_order(int a[], unsigned lendth);
void rotate_left(int a[], unsigned size, unsigned k);

int main()
{
	unsigned size, k, i;
	scanf("%u%u", &size, &k);
	int *a = (int *)malloc(size * sizeof(int));
	for (i = 0; i < size; ++i)
	{
		scanf("%d", &a[i]);
	}
	rotate_left(a, size, k);
	for (i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	free(a);
	return 0;
}

void rotate_left(int a[], unsigned size, unsigned k)
{
	reverse_order(a, size);
	reverse_order(a, size - k);
	reverse_order(&a[k], k);
}

void reverse_order(int a[], unsigned lendth)
{
	int i, tmp;
	for (i = 0; i < lendth / 2; ++i)
	{
		tmp = a[i];
		a[i] = a[(lendth - 1) - i];
		a[(lendth - 1) - i] = tmp;
	}
}