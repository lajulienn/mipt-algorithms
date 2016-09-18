#include <cstdio>
#include <cstdlib>
#include <cstring>

const int MAX_LEN = 100;
const int MAX_STRINGS = 10;

void insertion_sort_strings(const char *p[], int n);

int main()
{
	int n;
	//scanf("%d", &n);
	char buf[256];
	fgets(buf, sizeof(buf), stdin);
	sscanf(buf, "%d", &n);
	if (n > MAX_STRINGS)
	{
		printf("Error. Too big number\n");
		return 0;
	}	
	char *words[10];
	for (int i = 0; i < n; ++i)
	{
		words[i] = (char *)malloc(MAX_LEN + 2);
		fgets(words[i], MAX_LEN + 2, stdin);
		int lendth = strlen(words[i]);
		if (words[i][lendth - 1] == '\n')
			words[i][lendth - 1] = '\0';
	}
	printf("\n");
	for (int i = 0; i < n; ++i)
	{
		printf("[%s]\n", words[i]);
	}
	insertion_sort_strings((const char **)words, n);
	printf("\n");
	for (int i = 0; i < n; ++i)
	{
		printf("[%s]\n", words[i]);
		free(words[i]);
	}
	return 0;
}

void insertion_sort_strings(const char *p[], int n)
{
	const char *tmp;
	int i, k;
	for (i = 1; i < n; ++i)
	{
		tmp = p[i];
		k = i;
		while (k > 0)
		{
			if (strcmp(p[k - 1], tmp) > 0)
			{
				p[k] = p[k - 1];
				--k;
			}
			else
			{
				break;
			}
		}
		p[k] = tmp;
	}
}

