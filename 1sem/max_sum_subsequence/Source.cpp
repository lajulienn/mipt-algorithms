#include <cstdio>
#include <cstdlib>

int main() {
	int number;
	scanf("%d", &number);
	if (!number) {
		return 0;
	}
	int *array = (int *)malloc(number * sizeof(int));

	for (int i = 0; i < number; ++i)
		scanf("%d", &array[i]);

	struct Subsequence {
		int lastIndex = 0;
		int firstIndex = 0;
		int sum = 0;
	} Result, Tmp;

	Result.sum = INT_MIN;

//	Tmp.lastIndex = 1;
//	Tmp.sum = array[0];

	for (int i = 0; i < number; ++i) {
		Tmp.sum += array[i];
		++Tmp.lastIndex;

		if (Tmp.sum > Result.sum)
			Result = Tmp;

		if (Tmp.sum <= 0) {
			Tmp.firstIndex = i + 1;
			Tmp.lastIndex = i + 1;
			Tmp.sum = 0;
		}
	}
	printf("Max sum: %d\n", Result.sum);
	for (int i = Result.firstIndex; i < Result.lastIndex; ++i) {
		printf("%d ", array[i]);
	}
	printf("\n");
	free(array);
	return 0;
}
