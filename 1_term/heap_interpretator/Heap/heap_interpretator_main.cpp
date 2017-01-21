#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "functions_for_heap.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

int main()
{
		unsigned value;
		Heap myHeap = { 0 };
		heap_alloc(&myHeap, 2);
		char buf[256];
		while (true)
		{
			printf("> ");
			fgets(buf, sizeof(buf), stdin);
			char a[256] = "";
			heap_t b;
			int value_sscanf = sscanf(buf, "%s %u", &a, &b);
			if (value_sscanf == 2)
			{
				if (!strcmp(a, "push"))
					heap_add(&myHeap, b);
			}
			else if (value_sscanf == 1)
			{
				if (!(strcmp(a, "pop")))
					heap_pop(&myHeap);
				else if (!(strcmp(a, "top")))
				{
					heap_t top = 0;
					heap_t *ptr = (heap_t *)heap_top(&myHeap);
					if (heap_get_size(&myHeap))
						top = *ptr;
					printf("%u\n", top);
				}
				else if (!(strcmp(a, "size")))
				{

					int size = heap_get_size(&myHeap);
					printf("%d\n", size);
				}
				else if (!(strcmp(a, "cap")))
				{
					int capacity = heap_get_capacity(&myHeap);
					printf("%d\n", capacity);
				}
				else if (!strcmp(a, "push"))
					printf("error, no argument\n");
				else if (!strcmp(a, "end"))
				{
					heap_free(&myHeap);
					_CrtDumpMemoryLeaks();
					return 0;
				}
			}
			else
			{
				printf("error, something is wrong\n");
				return 0;
			}
			for (int k = 0; k < myHeap.size; ++k)
				printf("%d ", myHeap.data[k]);
			printf("\n");
		}
		heap_free(&myHeap);
		_CrtDumpMemoryLeaks();
		scanf("%d", &value);
		return 0;
}
