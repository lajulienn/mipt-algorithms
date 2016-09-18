#include <cstdio>
int count_words10(const char *filename);

int main()
{
	const char *filename = "D:\\text.txt";
	printf("%d\n", count_words10(filename));
	return 0;
}

int count_words10(const char *filename)
{
	int n = 0;
	char *ch[11]; //спросить
	FILE *fp = fopen(filename, "r");
	if (fp == NULL)
		printf("error\n");
	while (fscanf(fp, "%s", ch) == 1)
			++n;
	fclose(fp);
	return n;
}