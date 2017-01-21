#include <cstdio>
#include <cstring>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Functions.h"

class Checker
{
public:
	~Checker()
	{
		_CrtDumpMemoryLeaks();
	}
} checker;

int main() {
	List list;
	ListInitialisation(&list);
	Element *pointer = list.head;
	char buffer[256];
	while (true) {
		printf(">");
		fgets(buffer, sizeof(buffer), stdin);
		char instruction[256];
		int value = 0;
		int position = 0;
		int sscanf_value = sscanf(buffer, "%s%d%d", instruction, &value, &position);
		if (sscanf_value == 1) {
			if (!strcmp(instruction, "clear")) {
				Clear(&list);
				pointer = NULL;
			}
			else if (!strcmp(instruction, "dh")) {
				if (IsEmpty(&list)) {
					printf("List is already empty.\n");
				} else { 
					if (pointer == list.head)
						pointer = NULL;
					--list.size;
					DeleteFromHead(&list);
				}
			}
			else if (!strcmp(instruction, "dt")) {
				if (IsEmpty(&list)) {
					printf("List is already empty.\n");
				} else {
					if (pointer == list.tail)
						pointer = NULL;
					--list.size;
					DeleteFromTail(&list);
				}
			}
			else if (!strcmp(instruction, "dump"))
				Dump(&list);
			else if (!strcmp(instruction, "h"))
				GoToHead(&list, pointer);
			else if (!strcmp(instruction, "t"))
				GoToTail(&list, pointer);
			else if (!strcmp(instruction, "p")) {
				if (IsEmpty(&list)) {
					printf("This operation can't be done. Your list is empty.\n");
				} else if (pointer == NULL) {
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				} else {
					Pointer(pointer);
				}
			}
			else if (!strcmp(instruction, "n")) {
				if (pointer == NULL)
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				else 
					MoveToNext(pointer);
			}
			else if (!strcmp(instruction, "pr"))
				if (pointer == NULL)
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				else 
					MoveToPrevious(pointer);
			else if (!strcmp(instruction, "d")) {
				if (pointer == NULL)
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				else {
					--list.size;
					DeleteFromPointer(&list, pointer);
				}
			} else if (!strcmp(instruction, "s"))
				printf("Size of your list : %d\n", list.size);
			else if (!strcmp(instruction, "help"))
				Help();
			else if (!strcmp(instruction, "q")) {
				Clear(&list);
				break;
			}
			else {
				printf("Unknown instruction. Try again.\n");
			}
		} else if (sscanf_value == 2) {
			if (!strcmp(instruction, "ah"))
				AddToHead(&list, value);
			else if (!strcmp(instruction, "at"))
				AddToTail(&list, value);
			else if (!strcmp(instruction, "ib")) {
				if (pointer == NULL)
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				else
					InsertBeforePointer(&list, pointer, value);
			}
			else if (!strcmp(instruction, "ia")) {
				if (pointer == NULL)
					printf("Pointer = NULL. Please use instructions 'h' or 't'.\n");
				else
					InsertAfterPointer(&list, pointer, value);
			}
			else {
				printf("Unknown instruction. Try again.\n");
			}
		} else if (sscanf_value == 3) {
			if (position < 0)
				printf("Position must be non-negative integer.\n");
			else if (position > list.size - 1)
				printf("Position must be less than size of list.\n");
			else if (!strcmp(instruction, "iap"))
				InsertAfterPosition(&list, value, position);
			else if (!strcmp(instruction, "ibp"))
				InsertBeforePosition(&list, value, position);
			else {
				printf("Unknown instruction. Try again.\n");
			}
		} else {
			printf("Something is wrong. Try again.\n");
		}

	}
//	int *ptr = (int *)malloc(10);
	return 0;
}