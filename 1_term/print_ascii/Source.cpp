#include <cstdio>
#include <ctype.h>

int main()
{
	int i;
	for (i = 0; i < 256; ++i)
	{
		if (isgraph(i))
			printf("%c %d\n", i, i);
	}
	return 0;
}