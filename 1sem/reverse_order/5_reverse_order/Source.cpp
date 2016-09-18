#include <cstdio>
#include <cstdlib>

void reverse_order(int a[], unsigned lendth);

int main()
{
	int lendth, i;
	scanf("%d", &lendth);
	int *a = (int *)malloc(lendth * sizeof(int));
	for (i = 0; i < lendth; ++i)
	{
		scanf("%d", &a[i]);
	}
	reverse_order(a, lendth);
	for (i = 0; i < lendth; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
	free(a);
	return 0;
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