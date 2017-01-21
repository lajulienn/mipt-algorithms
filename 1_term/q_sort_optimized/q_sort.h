#ifndef Q_SORT
#define Q_SORT

int Urand();
double CountUnique(int *a, int n);
bool IsSorted(int *array, int size);
void Swap(int *a, int *b);
void QuickSort(int *a, int l, int r);
void RandomizedPartition(int *a, int *i, int *j);

#endif