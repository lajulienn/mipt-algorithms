#include <cstdio>

unsigned invert_bits(unsigned x);

int main()
{
	unsigned x;
	scanf("%u", &x);
	printf("%u", invert_bits(x));
	return 0;
}

unsigned invert_bits(unsigned x)
{
	return x ^ 255;
}