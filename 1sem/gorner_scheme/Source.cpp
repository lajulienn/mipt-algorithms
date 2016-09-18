#include <cstdio>

#define MAX 10

float horner_poly_value(float x, int n, float a[]);

int main()
{
	int n, i;
	scanf("%d", &n);
	if (n > MAX)
	{
		printf("Error");
		return 0;
	}
	float a[MAX];
	for (i = 0; i < n; ++i)
	{
		scanf("%f", &a[i]);
	}
	while (true)
	{
		float x;
		scanf("%f", &x);
		printf("%f", horner_poly_value(x, n, a));
	}

	return 0;
}

float horner_poly_value(float x, int n, float a[])
{
	int i;
	float res;
	res = a[0];
	for (i = 1; i < n; ++i)
	{
		res *= x;
		res += a[i];
	}
	return res;
}