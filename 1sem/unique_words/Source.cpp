#include <cstdio>
#include <cstdlib>
#include <cstring>

void insertion_sort_strings(const char **p, int n);
const int MAX_LEN = 100;

int main()
{
	FILE *text = fopen("D:\\text.txt", "r");
	char **words;
	words = (char **) malloc(sizeof(char *));
	int capacity = 1;
	if (words == NULL)
	{
		printf("Error\n");
		return 0;
	}
	int i = 0;
	char buf[MAX_LEN + 1];
	while (!feof(text))
	{
		fscanf(text, "%s", buf);
		if (i >= capacity)
		{
			words = (char **)realloc(words, 2 * sizeof(char *) * capacity);
			capacity *= 2;
		}
		words[i] = (char *) malloc(MAX_LEN + 1);
		strcpy(words[i], buf);
		++i;
	}
	/*for (int k = 0; k < i; ++k)
	{
		printf("[%s]\n", words[k]);
	}*/
	insertion_sort_strings((const char **)words, i);
	printf("\n");
	strcpy(buf, words[0]);
	int quantity = 1;
	free(words[0]);
	for (int k = 1; k < i; ++k)
	{
		if (!strcmp(buf, words[k]))
			++quantity;
		else
		{
			printf("%-15s %d\n", words[k], quantity);
			strcpy(buf, words[k]);
			free(words[k]);
		}
	}

	fclose(text);
	return 0;
}

void insertion_sort_strings(const char **p, int n)
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
				break;
		}
		p[k] = tmp;
	}
}

