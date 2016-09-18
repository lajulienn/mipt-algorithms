#ifndef FUNC
#define FUNC

typedef struct Heap Heap;
typedef unsigned data_t;

struct Heap
{
	data_t *data; // собственно массив с данными
	int size; // текущее количество элементов в куче
	int capacity; // ёмкость кучи (размер массива heap)
};

Heap * heapify(data_t *data, int size); // fixme

bool heap_alloc(struct Heap *heap, int initial_capacity);

int heap_get_size(const struct Heap *heap);

int heap_get_capacity(const struct Heap *heap);

const data_t *data_top(const struct Heap *heap);

bool heap_add(struct Heap *heap, data_t value);

bool heap_pop(struct Heap *heap);

void heap_free(struct Heap *heap);

unsigned do_command(Heap *heap);

void swap(data_t *a, data_t *b);

void heapify_down(Heap *A, int i);

int get_full_capacity(Heap *heap);

#endif