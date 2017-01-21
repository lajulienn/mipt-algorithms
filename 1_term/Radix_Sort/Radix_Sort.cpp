#include <cstdio>
#include <cstring>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

#include "Radix_sort.h"
#include <cstdlib>


class Checker
{
public:
	~Checker() {
		_CrtDumpMemoryLeaks();
	}
} checker;

void LsdRadixSort(unsigned *data, int n) {
	Queue queue[256];
	for (int i = 0; i < 256; ++i) {
		QueueInit(&queue[i]);
	}
	for (int j = 0; j < number_of_bytes; ++j) {
		for (int i = 0; i < n; ++i) {
			AddToQueue(data[i], &queue[GetByteValue(data[i], j)]);
		}
		int k = 0;
		for (int i = 0; i < 256; ++i) {
			while (queue[i].head != NULL) {
				data[k] = ExtractFromQueue(&queue[i]);
				++k;
			}
		}
	}
}

void QueueInit(Queue *queue) {
	queue->head = NULL;
	queue->tail = NULL;
}
void AddToQueue(unsigned value, Queue *queue) {
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = value;
	new_element->next = NULL;
	if (queue->head == NULL) {
		queue->head = new_element;
	} else {
		queue->tail->next = new_element;
	}
	queue->tail = new_element;
}
unsigned ExtractFromQueue(Queue *queue) {
	unsigned result = queue->head->value;
	Element *new_head = queue->head->next;
	free(queue->head);
	queue->head = new_head;
	if (queue->head == NULL)
		queue->tail = NULL;
	return result;
}
int GetByteValue(unsigned value, int byte) {
	return (value >> byte * 8) & 0xff;
}

bool IsSorted(unsigned *array, int size) {
	for (int i = 1; i < size; ++i)
		if (array[i] < array[i - 1])
			return false;
	return true;
}
unsigned Urand() {
	int result;
	char *tmp = (char *)&result;
	for (int i = 0; i < sizeof(int); ++i)
		tmp[i] = rand();
	result = *(int*)tmp;
	return (unsigned)result;
}
double CountUnique(unsigned *a, const int n) {
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
