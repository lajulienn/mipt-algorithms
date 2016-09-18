#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstdint>

uintmax_t urand();

int main()
{
	srand(time(NULL));
	for (int j = 0; j < 20; ++j)
	{
		uintmax_t value = urand();
		printf("%u ", value);
	}
	return 0;
}

uintmax_t urand()
{
	uintmax_t *result;
	int n = sizeof(uintmax_t);
	char *tmp = (char *)malloc(n);
	for (int i = 0; i < n; ++i)
		tmp[i] = rand();
	result = (uintmax_t *)tmp;
	free(tmp);
	return *result;
}