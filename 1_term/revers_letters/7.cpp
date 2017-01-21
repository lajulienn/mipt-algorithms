#include <cstdio>
#include <string.h>
#include <ctype.h>

int main()
{
	int i = 0;
	char ch[101] = "";
	while (1)
	{
		scanf("%s", &ch);
		if (!strcmp(ch, "end"))
			return 0;
		for (i = 100; i >= 0; --i)
		{
			if (ch[i] != '\0')
				printf("%c", ch[i]);
		}
		printf("\n");
	}
	return 0;
}
