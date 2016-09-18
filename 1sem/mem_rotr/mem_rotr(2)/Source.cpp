#include <cstdio>
#include <cstdlib>

void mem_rotr(void *p, unsigned size, unsigned k);
void rotate_right(unsigned char a[], unsigned size, unsigned k);
void reverse_order(unsigned char a[], unsigned lendth);
void binprint_uchar(unsigned char x);

int main()
{
	unsigned size, k, i;
	scanf("%u%u", &size, &k);
	unsigned char *p = (unsigned char *)malloc(size);
	if (p == NULL)
	{
		printf("Error, no memory");
		return 0;
	}
	for (i = 0; i < size; ++i)
	{
		unsigned x;
		scanf("%u", &x);
		p[i] = (unsigned char)x;
	}
	for (i = 0; i < size; ++i)
	{
		binprint_uchar(p[i]);
	}
	printf("\n");
	mem_rotr(p, size, k);
	for (i = 0; i < size; ++i)
	{
		printf("%d ", p[i]);
	}
	printf("\n");
	for (i = 0; i < size; ++i)
	{
		binprint_uchar(p[i]);
	}
	printf("\n");
	free(p);
	return 0;
}

void mem_rotr(void *p, unsigned size, unsigned k)
{
	unsigned byte_shift = k / 8, bit_shift = k % 8, i;
	unsigned char shift = 0, tmp;
	unsigned char *q = (unsigned char *)p;
	unsigned char buffer;

	rotate_right(q, size, byte_shift);

	for (i = 0; i < bit_shift; ++i)
	{
		shift = shift | (1 << i);
	}
	buffer = (q[size - 1] & shift) << (8 - bit_shift);
	q[size - 1] >>= bit_shift;

	for (i = size - 1; i > 0; --i)
	{
		q[i] |= q[i - 1] << (8 - bit_shift);
		q[i - 1] >>= bit_shift;
	}
	q[0] |= buffer;
}

void rotate_right(unsigned char a[], unsigned size, unsigned k)
{
	reverse_order(a, size);
	reverse_order(a, k);
	reverse_order(&a[k], size - k);
}

void reverse_order(unsigned char a[], unsigned lendth)
{
	unsigned char i, tmp;
	for (i = 0; i < lendth / 2; ++i)
	{
		tmp = a[i];
		a[i] = a[(lendth - 1) - i];
		a[(lendth - 1) - i] = tmp;
	}
}

void binprint_uchar(unsigned char x)
{
	int i, t;
	for (i = 7; i >= 0; --i)
	{
		t = (x & (1 << i)) >> i;
		printf("%d", t);
	}
	printf(" ");
}