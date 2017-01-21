#include <cstdio>

void hexprint_mem(const void *p, unsigned size);

int main()
{
	unsigned a, size;
	printf("Write a random number and size of memory\n");
	scanf("%u%u", &a, &size);
	hexprint_mem(&a, size);
	return 0;
}

void hexprint_mem(const void *p, unsigned size)
{
	int i;
	unsigned char *q = (unsigned char *)p;
	for (i = 1; i <= size; ++i)
	{
		printf("%4x ", *q);
		if (!(i % 7) && i)
			printf("\n");
		++q;
	}
}