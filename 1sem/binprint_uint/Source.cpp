#include <cstdio>

void binprint_uint(unsigned x);

int main()
{
	while (true)
	{
		int x;
		scanf("%d", &x);
		binprint_uint((unsigned)x);
	}
	return 0;
}

void binprint_uint(unsigned x)
{
	int i, t;
	int size = 8 * sizeof(x);
	for (i = size - 1; i >= 0; --i)
	{
		t = (x & (1 << i)) >> i;
		printf("%d", t);
	}
	printf("\n");
}