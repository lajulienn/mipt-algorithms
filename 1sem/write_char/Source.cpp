#include <cstdio>

int main()
{
	FILE *a = fopen("C:\\Users\\Юлия\\Documents", "r");
	if (!a)
	{
		printf("Cannot open\n");
		return 0;
	}
	char ch = 'c';
	fputc(ch, a);
	printf("%d %d %d", fgetc(a), ferror(a), feof(a));
	fclose(a);
	return 0;
}