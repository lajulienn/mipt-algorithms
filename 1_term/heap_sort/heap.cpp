#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "heap.h"


bool heap_alloc(struct Heap *heap, int initial_capacity) {
	if (heap->capacity || heap->data || heap->size)
		return false;
	heap->data = (data_t *)malloc(initial_capacity * sizeof(data_t));
	if (heap->data == NULL)
	{
		printf("Sorry, no memory");
		return false;
	}
	heap->size = 0;
	heap->capacity = initial_capacity;
	return true;
}

/*Heap * heapify(data_t *data, int size) {
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	heap->data = data;
	heap->size = size;
	heap->capacity = size;

	for (int i = get_full_capacity(heap) / 2 - 1; i >= 0; --i) {
		heapify_down(heap, i);
	}

	return heap;
}*/

int heap_get_size(const struct Heap *heap) {
	return heap->size;
}

int heap_get_capacity(const struct Heap *heap) {
	return heap->capacity;
}

const data_t *data_top(const struct Heap *heap) {
	if (!heap->data[0])
		return &(heap->data[0]);
}

bool heap_add(struct Heap *heap, data_t value) {
	if (heap->size == heap->capacity)
	{
		heap->data = (data_t *)realloc(heap->data, heap->capacity * 2 * sizeof(data_t));
		if (heap->data == NULL)
		{
			printf("Sorry, no memory");
			return false;
		}
		heap->capacity *= 2;
	}
	heap->data[heap->size] = value;
	int i = heap->size;
	int parent = (i - 1) / 2;
	while (i && heap->data[parent] < value)
	{
		swap(&(heap->data[i]), &(heap->data[parent]));
		i = parent;
		parent = (i - 1) / 2;
	}
	++(heap->size);
	return true;
}

void heap_free(struct Heap *heap)
{
	free(heap->data);
	free(heap);
	return;
}
void swap(data_t *a, data_t *b)
{
	data_t tmp = *a;
	*a = *b;
	*b = tmp;
}

bool heap_pop(struct Heap *heap) {
	if (!heap_get_size(heap))
		return false;
	--(heap->size);
	swap(&(heap->data[0]), &(heap->data[heap->size]));
	heapify_down(heap, 0);
	return true;
}

void heapify_down(Heap *A, int i) {
	int child1;
	int child2;
	int greatest = i;
	do {
		i = greatest;
		child1 = 2 * i + 1;
		child2 = 2 * i + 2;
		if (child1 < A->size && A->data[greatest] < A->data[child1])
			greatest = child1;
		if (child2 < A->size && A->data[greatest] < A->data[child2])
			greatest = child2;
		swap(&(A->data[i]), &(A->data[greatest]));
	} while (greatest != i);
}

int get_full_capacity(Heap *heap) {
	int capacity = 1;
	while (heap->size >= capacity) {
		capacity *= 2;
	}
	return capacity - 1;
}

/*Heap * heapify(data_t *data, int size) {
	Heap *heap = (Heap *)malloc(sizeof(Heap));
	heap->data = (data_t *)malloc(sizeof(data_t));
	heap->size = 1;
	heap->capacity = 1;
	
	heap->data[0] = data[0];
	for (int i = 1; i < size; ++i) {
		heap_add(heap, data[i]);
	}
	printf("\n\n\n");
	for (int i = 0; i < size; ++i) {
		printf("%-12u", heap->data[i]);
		if ((i + 1) % 4 == 0)
			printf("\n");
	}
	
	return heap;*/

Heap * heapify(data_t *data, int size) {
Heap *heap = (Heap *)malloc(sizeof(Heap));
heap->data = data;
heap->size = size;
heap->capacity = size;

for (int i = get_full_capacity(heap) / 2 - 1; i >= 0; --i) {
heapify_down(heap, i);
}

return heap;
}