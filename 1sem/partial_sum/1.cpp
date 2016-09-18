#include <cstdio>

int main()
{
	typedef float MyType;
	const double answer = 1.6449340668482264;
	MyType sum = 0;
	for (MyType i = 1; i <= 1000000; ++i)
	{
		MyType x = 1.0 / i;
		sum += x / i;
	}
	printf("%e\t%e\n", sum, answer - sum);
	sum = 0;
	for (MyType i = 1000000; i >= 1; --i)
	{
		MyType x = 1.0 / i;
		sum += x / i;
	}
	printf("%e\t%e\n", sum, answer - sum);
	return 0;
}