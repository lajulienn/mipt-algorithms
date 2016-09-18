#ifndef MERGE
#define MERGE

void MergeSort(int *data, int N);
bool Sort(int *data, int *buffer, int l, int r);
bool Merge(int *data, int *buffer, int l, int m, int r, bool left_in_buffer, bool right_in_buffer);
bool IsSorted(int *array, int size);
int Urand();
double CountUnique(int *a, int n);

#endif