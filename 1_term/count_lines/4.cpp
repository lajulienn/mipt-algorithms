#include <cstdio>
#include <string.h>


int count_lines(const char *filename);

int main()
{
	const char *filename = "D:\\text.txt";
	printf("%d", count_lines(filename));
	return 0;
}

int count_lines(const char *filename)
{
	int  n = 0;
	char ch;
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		printf("error\n");
	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			++n;
	}
	fclose(fp);
	return n + 1;
}