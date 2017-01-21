#include "Shell_sort.h"
#include <cstdlib>
#include <cmath>


void ShellSort(int* a, int n) {
	int i, j, k, temp;
	int *Step = GenerateSequence(n, &k);
	for (k; k >= 0; --k) {
		for (i = k; i< n; i++) {
			temp = a[i];
			for (j = i; j >= k; j -= k) {
				if (temp < a[j - k]) 
					a[j] = a[j - k];
				else
					break;
			}
			a[j] = temp;
		}
	}
}

int * GenerateSequence(const int n, int *counter) {
	int i = 0, j = 0;
	float exp = 0; 
	int *Step = (int *)malloc(((int)n / 2) * sizeof(int));

	*counter = 0;
	while (exp = pow(2, i) * pow(3, j) < (float)n / 2) {
		Step[*counter] = exp;
		if (*counter % 2 == 0)
			++i;
		else
			++j;
		++(*counter);
	}
	int *a = Step;
	free(Step);
	return a;
}
bool IsSorted(int *array, int size) {
	for (int i = 1; i < size; ++i)
		if (array[i] < array[i - 1])
			return false;
	return true;
}
int Urand() {
	int result;
	char *tmp = (char *)&result;
	for (int i = 0; i < sizeof(int); ++i)
		tmp[i] = rand();
	result = *(int*)tmp;
	return result;
}
double CountUnique(int *a, int n) {
	unsigned count = 1;
	for (int i = 1; i < n; ++i) {
		if (a[i] != a[i - 1])
			++count;
	}
	return (double)count / n;
}