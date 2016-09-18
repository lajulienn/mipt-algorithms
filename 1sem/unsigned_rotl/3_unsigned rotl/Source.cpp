#include <cstdio>
#include <cstdlib>

unsigned rotl(unsigned x, unsigned);

int main()
{
	unsigned x, k;
	scanf("%u%u", &x, &k);
	printf("%u", rotl(x, k));
	return 0;
}

unsigned rotl(unsigned x, unsigned k)
{
	int size = 8 * sizeof(x);
	
	k %= size;
	
	unsigned right_part = x >> (size - k);
	unsigned result = (x << k) | right_part;
	/*unsigned res = 0, i;
	while (k >= 8)
	{
		k -= 8;
	}
	for (i = 0; i < 8 - k; ++i)
	{
		res = res | ((x & (1 << i)) << k);
	}
	for (i = 8 - k; i < 8; ++i)
	{
		res = res | ((x & (1 << i)) >> 8 - k);
	}
	return res;*/
	return result;
}
