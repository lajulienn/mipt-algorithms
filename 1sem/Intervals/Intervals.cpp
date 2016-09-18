#include <cstdio>
#include <cstdlib>

const int  MAX_NUMBER_OF_INTERVALS = 100000;

struct Interval {
	int left_bound;
	int right_bound;
};

int Compare(const Interval *a, const Interval *b);

int main() {
	int bound = 0;
	char buffer[256];
	scanf("%d", &bound);
	Interval intervals[MAX_NUMBER_OF_INTERVALS];
	int amount_of_intervals = 0;
	do {
		scanf("%d%d", &intervals[amount_of_intervals].left_bound, &intervals[amount_of_intervals].right_bound);
		++amount_of_intervals;
	} while (intervals[amount_of_intervals - 1].left_bound != 0
		    || intervals[amount_of_intervals - 1].right_bound != 0);
	--amount_of_intervals;
	qsort(intervals, amount_of_intervals, sizeof(Interval), (int(*)(const void *, const void *))Compare);
	
	int *used = (int *)malloc(amount_of_intervals * sizeof(int));
	
	int point = 0;
	int i = 0;
	int used_count = 0;

	if (amount_of_intervals == 0 || intervals[i].left_bound > point
		|| intervals[amount_of_intervals - 1].right_bound <= 0) {
		printf("No solution\n");
		free(used);
		return 0;
	}

	int max = 0;
	while (point < bound) {
		while (i < amount_of_intervals && intervals[i].left_bound <= point) {
			if (intervals[i].right_bound > intervals[max].right_bound)
				max = i;
			++i;
		}

		if (used_count && max == used[used_count - 1]) {
			printf("No solution\n");
			free(used);
			return 0;
		}

		used[used_count] = max;
		++used_count;

		point = intervals[max].right_bound;
	}
	printf("%d\n", used_count);
	for (int i = 0; i < used_count; ++i)
		printf("%d %d\n", intervals[used[i]].left_bound, intervals[used[i]].right_bound);
	
	free(used);
	return 0;
}
int Compare(const Interval *a, const Interval *b) {
	return a->left_bound == b->left_bound
		? a->right_bound - b->right_bound
		: a->left_bound - b->left_bound;
}