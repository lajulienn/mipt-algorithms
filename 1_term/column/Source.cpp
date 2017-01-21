#include <cstdio>

#define QUAN 10
#define MAX 20

int main()
{
	int num[QUAN];
	int i, k;
	for (i = 0; i < QUAN; ++i)
	{
		scanf("%d", &num[i]);
		if (num[i] > MAX)
		{
			printf("Error");
			return 0;
		}
	}
	printf("\n");
	for (k = 0; k < MAX; ++k)
	{
		for (i = 0; i < QUAN; ++i)
		{
			if (num[i] > 0)
			{
				printf("*");
				printf(" ");
				--num[i];
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	return 0;
}