#include <cstdio>
#include <cstdlib>
#include <cmath>

const double ANSWER = 1.6449340668482264;

void fill_direct(float *a, int n);
void fill_mixed(float *a, int n);
float direct_sum(const float *a, int n);
float reverse_sum(const float *a, int n);
float kahan_sum(const float *a, int n);

int main()
{
	int n;
	scanf("%d", &n);
	float *a = (float *)malloc(n * sizeof(float));
	fill_direct(a, n);
	fill_mixed(a, n);
	//printf("\n");
	float ds = direct_sum(a, n), rs = reverse_sum(a, n), ks = kahan_sum(a, n);
	printf("%e\t%e\n%e\t%e\n%e\t%e\n", ds, fabs(ds - ANSWER), rs, fabs(rs - ANSWER), ks, fabs(ks - ANSWER));

	return 0;
}

void fill_direct(float *a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		float d = 1.0 / (i + 1);
		a[i] = d / (i + 1);

//		printf("%f %f\n", d, a[i]);
	}
}

void fill_mixed(float *a, int n)
{
	float d;
	for (int i = 0; i < n; ++i)
	{
		if (!(i % 2))
		{
			d = 1.0 / (i + 1);
			a[i] = d / (i + 1);
		}
		else
		{
			d = 1.0 / (n + 1 - i);
			a[i] = d /(n + 1 - i);
		}
		//printf("%f\n", a[i]);
	}
}


float direct_sum(const float *a, int n)
{
	float sum = 0;
	for (int i = 0; i < n; ++i)
	{
		sum += a[i];
	}
	return sum;
}

float reverse_sum(const float *a, int n)
{
	float sum = 0;
	for (int i = n - 1; i >= 0; --i)
	{
		sum += a[i];
	}
	return sum;
}

float kahan_sum(const float *a, int n)
{
	float sum = 0;
	float c = 0;
	for (int i = 0; i < n; ++i)
	{
		float y = a[i] - c;
		float t = sum + y;
		c = (t - sum) - y;
		sum = t;
	}
	return sum;
}