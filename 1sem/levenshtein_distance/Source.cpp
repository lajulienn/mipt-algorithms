#include <cstdio>
#include <cstring>
#include <cstdlib>

int Min3(int a, int b, int c);
int levenshtein(const char *s1, const char *s2);

int main() {
	const int MAX_LEN = 15;
	char string1[MAX_LEN];
	char string2[MAX_LEN];
	scanf("%s%s", string1, string2);
	int d = levenshtein(string1, string2);
	printf("%d\n", d);

	return 0;
}

int levenshtein(const char *s1, const char *s2) {
	unsigned x, y, length1, length2;
	length1 = strlen(s1);
	length2 = strlen(s2);

	int **matrix = (int **)malloc(sizeof(int *) * (length1 + 1));
	if (!matrix) {
		printf("No memory\n");
		return 0;
	}
	for (unsigned i = 0; i <= length1; ++i) {
		matrix[i] = (int *)malloc((length2 + 1) * sizeof(int));
		if (!matrix[i]) {
			printf("No memory\n");
			return 0;
		}
	}

	for (x = 0; x <= length1; x++)
		matrix[x][0] = x;
	for (y = 1; y <= length2; y++)
		matrix[0][y] = y;
	for (x = 1; x <= length1; x++)
		for (y = 1; y <= length2; y++)
			matrix[x][y] = Min3(matrix[x - 1][y] + 1, matrix[x][y - 1] + 1, matrix[x - 1][y - 1] + (s1[y - 1] == s2[x - 1] ? 0 : 1));

	int d = matrix[length1][length2];

	for (unsigned i = 0; i <= length1; ++i)
		free(matrix[i]);
	free(matrix);

	return d;
}

int Min3(int a, int b, int c) {
	return ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)));
}
