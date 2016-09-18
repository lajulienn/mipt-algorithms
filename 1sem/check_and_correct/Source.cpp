#include <cstdio>

int main()
{
	int a[] = {1, 2, 3};
	const int *p = a;
	a[0] = 2; //исправлено с *p на a[0]
	int * q = a; //убираем const
	q[0] = 2;
	++q;
	return 0;
}