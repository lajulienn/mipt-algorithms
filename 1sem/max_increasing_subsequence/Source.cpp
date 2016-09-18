#include <cstdio>
#include <cstdlib>

int binary_search(int*a, int first, int n, int key);

int main() {
	int number;
	scanf("%d", &number);
	if (number <= 0)
		return 0;
	int *data = (int *)malloc(number * sizeof(int));
	if (!data) {
		printf("No memory\n");
		return 0;
	}

	for (int i = 0; i < number; ++i)
		scanf("%d", &data[i]);

	int *previous = (int *)malloc(number * sizeof(int));
	if (!previous) {
		printf("No memory\n");
		return 0;
	}
	
	int *sequences = (int *)malloc((number + 1) * sizeof(int));
	if (!sequences) {
		printf("No memory\n");
		return 0;
	}
	sequences[0] = INT_MIN;
	for (int i = 1; i <= number; ++i)
		sequences[i] = INT_MAX;
	
	int *indexes = (int *)malloc((number + 1) * sizeof(int));
	if (!indexes) {
		printf("No memory\n");
		return 0;
	}
	for (int i = 0; i <= number; ++i)
		indexes[i] = -1;

	for (int i = 0; i < number; ++i) {
		int k = binary_search(sequences, 0, number, data[i]);
	//	for (int k = 1; k <= number; ++k) {
	//		if (data[i] > sequences[k - 1] && data[i] < sequences[k]) { //use bin_search
				sequences[k] = data[i];
				indexes[k] = i;
				if (k > 0)
					previous[i] = indexes[k - 1];
	//		}
	//	}
	}
	// n = 1 ????
	int max_length = 0;	
	while (max_length < number && sequences[max_length + 1] != INT_MAX)
		++max_length;
	printf("Length = %d\n", max_length);
	int *answer = (int *)malloc(max_length * sizeof(int));
	int tmp = indexes[max_length];
	for (int i = max_length - 1; i >= 0; --i) {
		answer[i] = data[tmp];
		tmp = previous[tmp];
	}
	for (int i = 0; i < max_length; ++i)
		printf("%d ", answer[i]);

	free(data);
	free(sequences);
	free(indexes);
	free(previous);
	free(answer);
	return 0;
}

int binary_search(int*a, int first, int n, int key) {
	int last = first + n;
	while (first < last) {
		int mid = first + (last - first) / 2;

		if (key <= a[mid])
			last = mid;
		else
			first = mid + 1;
	}

	if (last < n && a[last] >= key) {
		return last;
	}
	else if (n == 1)
		return 1;
	else
		return -1;
}