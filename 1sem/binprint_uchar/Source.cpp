#include <cstdio>

void binprint_uchar(unsigned char x);

int main()
{
	int x;
	scanf("%d", &x);
	binprint_uchar(x);
	return 0;
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