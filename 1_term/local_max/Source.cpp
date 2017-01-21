#include <cstdio>

int main()
{
	int temp[2], i, num = 0, next;
	for (i = 0; i < 2; ++i)
	{
		scanf("%d", &temp[i]);
	}
	if (temp[0] > temp[1]) 
		++num;
	if (temp[1] < 0)
	{
		printf("%d\n", num);
		return 0;
	}
	while (true)
	{
		scanf("%d", &next);
		if (next < 0)
		{
			if (temp[1] > temp[0]) ++num;
			printf("%d\n", num);
			return 0;
		}
		if ((temp[1] > next) && (temp[1] > temp[0])) ++num;
		temp[0] = temp[1];
		temp[1] = next;
	}
	return 0;
}