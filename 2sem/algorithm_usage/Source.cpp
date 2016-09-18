#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iterator>
#include <cassert>
#include <functional>

using namespace std;

//struct Compare {
//	bool operator() (int x, int y) { return x > y; }
//} compare;

int main() {
	srand(unsigned(time(0)));
	vector<int> src_vector(1000);
	generate(src_vector.begin(), src_vector.end(), []() { return rand() % 100; });

	vector<int> my_vector;
	copy(src_vector.begin(), src_vector.end(), back_inserter(my_vector));

	random_shuffle(my_vector.begin(), my_vector.end());

	sort(my_vector.begin(), my_vector.end(), greater<int>());

	reverse(my_vector.begin(), my_vector.end());

	assert(my_vector.front() == *min_element(src_vector.begin(), src_vector.end()));
	assert(my_vector.back() == *max_element(src_vector.begin(), src_vector.end()));

	vector<int> permutation(1000);
	int i = 0;
	generate(permutation.begin(), permutation.end(), [&i]() { return i++; });

	sort(permutation.begin(), permutation.end(), [&src_vector](int x, int y) { return src_vector[x] < src_vector[y]; });

	vector<int> sorted;
	transform(permutation.begin(), permutation.end(), back_inserter(sorted), [&src_vector](int i) { return src_vector[i]; });

	assert(is_sorted(sorted.begin(), sorted.end()));
	assert(equal(sorted.begin(), sorted.end(), my_vector.begin()));

	vector<int> counts(100);
	i = 0;
	generate(counts.begin(), counts.end(), [&sorted, &i]() {
		int cnt = count(sorted.begin(), sorted.end(), i);
		assert(cnt == upper_bound(sorted.begin(), sorted.end(), i) - lower_bound(sorted.begin(), sorted.end(), i));
		++i;
		return cnt;
	});
	int sum = 0;
	for_each(counts.begin(), counts.end(), [&sum](int x) { sum += x; });
	assert(sum == 1000);

	for_each(sorted.begin(), sorted.end(), [](int x) { cout << x << " "; });

	return 0;
}