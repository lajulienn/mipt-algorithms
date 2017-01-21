#include <cstdio>

void binprint_mem(const void *p, unsigned size);
void binprint_uchar(unsigned char x);

int main()
{
	unsigned a, size;
	printf("Enter a random number and size of memory you want to see\n");
	scanf("%u%u", &a, &size);
	binprint_mem(&a, size);
	return 0;
}

void binprint_mem(const void *p, unsigned size)
{
	unsigned i;
	unsigned char *q = (unsigned char*)p;
	for (i = 1; i <= size; ++i)
	{
		binprint_uchar(*q);
		printf(" ");
		if (!(i % 8))
			printf("\n");
		++q;
	}
	printf("\n");
}

void binprint_uchar(unsigned char x)
{
	int i, t;
	for (i = 7; i >= 0; --i)
	{
		t = (x & (1 << i)) >> i;
		printf("%d", t);
	}
}