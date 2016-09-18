#include <cstdio>
#include <cstdlib>
#include <string.h>
#include "heapf.h"

const int HEAP_CAPACITY = 1024;
const int BUF_SIZE = 100;
const int COMMAND_SIZE = 10;
int main()
{
	struct Heap heap = { 0 };
	heap_alloc(&heap, HEAP_CAPACITY);
	char buf[BUF_SIZE], command[COMMAND_SIZE];
	int n = 0;
	while (1)
	{
		printf("> ");
		fgets(buf, sizeof(buf), stdin);
		int r = sscanf(buf, "%s %d", &command, &n);
		if (r <= 0)
		{
			printf("Error! No command\n");
			continue;
		}
		if (!(strcmp("push", command)))
		{
			if (r == 1)
				printf("Error! No argument!\n");
			else
			{
				heap_add(&heap, n);
				printf("\n");
			}
		}
		else if (!(strcmp("pop", command)))
		{
			if (heap_top(&heap) == NULL)
				printf("Error! No top!\n");
			else
			{
				printf("%d\n", *heap_top(&heap));
				heap_pop(&heap);
			}
		}
		else if (!(strcmp(command, "top")))
		{
			if (heap_top(&heap) == NULL)
				printf("Error! No top\n");
			else
				printf("%d\n", *heap_top(&heap));
		}
		else if (!(strcmp(command, "size")))
			printf("%d\n", heap_get_size(&heap));
		else if (!(strcmp(command, "cap")))
			printf("%d\n", heap_get_capacity(&heap));
		else if (!(strcmp(command, "end")))
		{
			heap_free(&heap);
			return 0;
		}
		else
			printf("Error! Unknown command!\n");
	}
}