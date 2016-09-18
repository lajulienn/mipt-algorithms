#include "Merge_Sort.h"
#include <cstdlib>
#include <cstring>

void MergeSort(int *data, const int N) {
	int *buffer = (int *)malloc(N * sizeof(int));
	bool in_buffer = Sort(data, buffer, 0, N - 1);
	if (in_buffer) {
		memcpy(data, buffer, (N) * sizeof(int));
	}
	free(buffer);
}
bool Sort(int *data, int *buffer, int l, int r) {
	if (l >= r)
		return false;
	int m = (l + r) / 2;
	bool left_in_buffer = Sort(data, buffer, l, m);
	bool right_in_buffer = Sort(data, buffer, m + 1, r);
	return Merge(data, buffer, l, m, r, left_in_buffer, right_in_buffer);
}
bool Merge(int *data, int *buffer, int l, int m, int r, bool left_in_buffer, bool right_in_buffer) {
	bool in_buffer = left_in_buffer == right_in_buffer ? !right_in_buffer : right_in_buffer;
	int *destination = in_buffer ? buffer + l : data + l;
	int *left_part = left_in_buffer ? buffer + l : data + l;
	int left_size = m - l + 1;
	int *right_part = right_in_buffer ? buffer + m + 1 : data + m + 1;
	int right_size = r - m;

	int i, j;
	i = j = 0;
	while (i < left_size && j < right_size) {
		if (left_part[i] <= right_part[j]) {
			*destination = left_part[i];
			++i;
		} else {
			*destination = right_part[j];
			++j;
		}
		++destination;
	}
	
	while (i < left_size) {
		*destination = left_part[i];
		++i;
		++destination;
	}

	if (in_buffer != right_in_buffer) {
		while (j < right_size) {
			*destination = right_part[j];
			++j;
			++destination;
		}
	}

	return in_buffer;
}
bool IsSorted(int *array, const int size) {
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
double CountUnique(int *a, const int n) {
	if (n == 1)
		return 1;
	unsigned count = 0;
	if (a[0] != a[1])
		++count;
	for (int i = 1; i < n - 1; ++i) {
		if (a[i] != a[i - 1] && a[i] != a[i + 1])
			++count;
	}
	if (a[n - 2] != a[n - 1])
		++count;
	return (double)count / n;
}


/*if (left_order == right_order) {
if (left_order == true) {
data = a;
buffer = b;
order = false;
} else {
data = b;
buffer = a;
order = true;
}
for (k = l; k <= r; ++k) {
if (i <= m && j <= r) {
if (data[i] < data[j]) {
buffer[k] = data[i];
++i;
} else {
buffer[k] = data[j];
++j;
}
} else if (i > m && j <= r) {
buffer[k] = data[j];
++j;
} else if (j > r && i <= m) {
buffer[k] = data[i];
++i;
}
}
} else if (left_order == true) {
data = a;
buffer = b;
order = false;
for (k = l; k <= r; ++k) {
if (i <= m && j <= r) {
if (data[i] < buffer[j]) {
buffer[k] = data[i];
++i;
} else {
buffer[k] = buffer[j];
++j;
}
}
}
} else {
data = b;
buffer = a;
order = true;
for (k = l; k <= r; ++k) {
if (i <= m && j <= r) {
if (data[i] < buffer[j]) {
buffer[k] = data[i];
++i;
} else {
buffer[k] = buffer[j];
++j;
}
}
}
}*/