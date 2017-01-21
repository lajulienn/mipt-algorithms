#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "functions_for_heap.h"


bool heap_alloc(struct Heap *heap, int initial_capacity)
{
	if (heap->capacity || heap->data || heap->size)
		return false;
	heap->data = (heap_t *)malloc(initial_capacity * sizeof(heap_t));
	if (heap->data == NULL)
	{
		printf("Sorry, no memory");
		return false;
	}
	heap->size = 0;
	heap->capacity = initial_capacity;
	return true;
}
int heap_get_size(const struct Heap *heap)
{
	return heap->size;
}
int heap_get_capacity(const struct Heap *heap)
{
	return heap->capacity;
}
const heap_t *heap_top(const struct Heap *heap)
{
	if (!heap->data[0])
		return &(heap->data[0]);
}
bool heap_add(struct Heap *heap, heap_t value)
{
	if (heap->size == heap->capacity)
	{
		heap->data = (heap_t *)realloc(heap->data, heap->capacity * 2 * sizeof(heap_t));
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
	//free(heap);
}
void swap(heap_t *a, heap_t *b)
{
	heap_t tmp = *a;
	*a = *b;
	*b = tmp;
}

//void heapify_down(Heap *A, int i);
void heapify_down(Heap *A, int i);
bool heap_pop(struct Heap *heap)
{
	if (!heap_get_size(heap))
		return false;
	swap(&(heap->data[0]), &(heap->data[heap->size - 1]));
	heap->data[heap->size - 1] = 0;
	--(heap->size);
	int i = 0;
	heapify_down(heap, i);
	return true;
}
void heapify_down(Heap *A, int i)
{
	/*int leftChild, rightChild, largest;
	while (true)
	{
	leftChild = 2 * i + 1;
	rightChild = 2 * i + 1;
	largest = i;
	if (leftChild > A->size || rightChild > A->size)
	break;
	if (A->data[leftChild] > A->data[i])
	{
	swap(&(A->data[leftChild]), &(A->data[i]));
	i = leftChild;
	}
	else if (A->data[rightChild] > A->data[i])
	{
	swap(&(A->data[rightChild]), &(A->data[i]));
	i = rightChild;
	}
	else break;
	}*/
	int child1;
	int child2;
	int greatest = i;
	do {
		i = greatest;
		child1 = 2 * i + 1;
		child2 = 2 * i + 2;
		if (child1 < A->size && A->data[i] < A->data[child1])
			greatest = child1;
		if (child2 < A->size && A->data[child1] < A->data[child2])
			greatest = child2;
		swap(&(A->data[i]), &(A->data[greatest]));
	} while (greatest != i);
}