#include <cstdio>
int main()
{

	return 0;
}

unsigned count_unique(int *a, int n)
{
	unsigned count = 0;
	for (int i = 1; i < n; ++i)
	{
		if (a[i] != a[i - 1])
			++count;
	}
	return count;
}