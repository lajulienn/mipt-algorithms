#include <cstdio>

void binprint_uint(unsigned x);
void binprint_mem(const void *p, unsigned size);
void binprint_uchar(unsigned char x);

int main()
{
	int value = 0x04030201;
	binprint_uint(value);
	binprint_mem(&value, sizeof(value));
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