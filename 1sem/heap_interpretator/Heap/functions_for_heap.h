#ifndef FUNC
#define FUNC

typedef struct Heap Heap;
typedef unsigned heap_t;

struct Heap
{
	heap_t *data; // собственно массив с данными
	int size; // текущее количество элементов в куче
	int capacity; // ёмкость кучи (размер массива heap)
};

bool heap_alloc(struct Heap *heap, int initial_capacity);
int heap_get_size(const struct Heap *heap);
int heap_get_capacity(const struct Heap *heap);
const heap_t *heap_top(const struct Heap *heap);
bool heap_add(struct Heap *heap, heap_t value);
bool heap_pop(struct Heap *heap);
void heap_free(struct Heap *heap);
unsigned do_command(Heap *heap);
void swap(heap_t *a, heap_t *b);

#endif