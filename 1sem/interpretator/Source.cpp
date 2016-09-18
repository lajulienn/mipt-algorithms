#include <cstdio>
#include <cstdlib>
#include <string.h>

int main()
{ 
	char buf[256];
	while (true)
	{
		printf("> ");
		fgets(buf, sizeof(buf), stdin);
		char a[256] = "", b[256] = "";
		int value_sscanf = sscanf(buf, "%s %s", &a, &b);
		if (value_sscanf == 2)
		{
			if (!strcmp(a, "say"))
				printf("%s\n", b);
			else if (!strcmp(a, "reverse"))
			{
				for (int i = strlen(b) - 1; i >= 0; --i)
						printf("%c", b[i]);
				printf("\n");
			}
		}
		else if (value_sscanf == 1)
		{
			if (!(strcmp(a, "hi")))
				printf("Hello!\n");
			else if (!(strcmp(a, "bye")))
				return 0;
			else if (!strcmp(a, "reverse"))
			{
				printf("error, no argument\n");
				continue;
			}
			else if (!strcmp(a, "say"))
			{
				printf("error, no argument\n");
				continue;
			}
		}
		else
			continue;
	}
	return 0;
}