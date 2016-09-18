#ifndef RADIX
#define RADIX

const int number_of_bytes = sizeof(unsigned);

struct Element{
	unsigned value;
	Element *next;
};
struct Queue {
	Element *head;
	Element *tail;
};

//typedef struct Queue Queue;
//typedef struct Element Element;

void LsdRadixSort(unsigned *data, int n);
void QueueInit(Queue *queue);
void AddToQueue(unsigned value, Queue *queue);
unsigned ExtractFromQueue(Queue *queue);
int GetByteValue(unsigned value, int byte);
bool IsSorted(unsigned *array, int size);
unsigned Urand();
double CountUnique(unsigned *a, const int n);

#endif