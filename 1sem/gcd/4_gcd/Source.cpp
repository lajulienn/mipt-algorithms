#include <cstdio>

int gcd(int a, int b);

int main()
{
	int  a, b;
	scanf("%d%d", &a, &b);
	printf("%d\n", gcd(a, b));
	return 0;
}

int gcd(int a, int b)
{
	int check;
	if (a < 0)
		a = -a;
	if (b < 0)
		b = -b;
	if (a == 0)
		return b;
	if (b == 0)
		return a;
	while (a != b)
	{
		a > b ? a -= b : b -= a;
		//printf("%d, %d\n", a, b);
		//scanf("%d", &check);
	}
	return a;
}