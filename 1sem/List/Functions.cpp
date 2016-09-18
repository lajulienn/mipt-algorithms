#include "Functions.h"
#include <cstdio>
#include <cstdlib>

void ListInitialisation(List *list) {
	list->head = NULL;
	list->tail = NULL;
	list->size = 0;
}
void Clear(List *list) {
	while (!IsEmpty(list)) {
		Element *tmp = list->head->next;
		free(list->head);
		list->head = tmp;
	}
	list->tail = NULL;
	list->size = 0;
}
void AddToHead(List *list, int value) {
	++list->size;
	Element *new_element = (Element *)malloc(sizeof(Element));

	new_element->value = value;
	if (IsEmpty(list)) {
		list->head = new_element;
		list->tail = new_element;
		list->head->previous = NULL;
		list->head->next = NULL;
	} else {
		new_element->next = list->head;
		list->head->previous = new_element;
		new_element->previous = NULL;
		list->head = new_element;
	}
}
void AddToTail(List *list, int value) {
	++list->size;
	Element *new_element = (Element *)malloc(sizeof(Element));

	new_element->value = value;
	if (IsEmpty(list)) {
		list->head = new_element;
		list->tail = new_element;
		new_element->previous = NULL;
		new_element->next = NULL;
	} else {
		new_element->next = NULL;
		new_element->previous = list->tail;
		list->tail->next = new_element;
		list->tail = new_element;
	}
}
void DeleteFromHead(List *list) {
	Element *tmp = list->head->next;
	free(list->head);
	list->head = tmp;
	if (!IsEmpty(list))
		list->head->previous = NULL;
	else
		list->tail = NULL;
}
void DeleteFromTail(List *list) {
	Element *tmp = list->tail->previous;
	free(list->tail);
	list->tail = tmp;
	if (list->tail != NULL)
		list->tail->next = NULL;
	else
		list->head = NULL;
}
void Dump(List *list) {
	for (Element *pointer = list->head; pointer != NULL; pointer = pointer->next)
		printf("%d  ", pointer->value);
	printf("\n");
}
void InsertAfterPosition(List *list, int value, int position) {
	++list->size;
	Element *pointer = list->head;
	for (int i = 0; i < position; ++i) {
		pointer = pointer->next;
	}
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = value;

	new_element->previous = pointer;
	new_element->next = pointer->next;
	pointer->next = new_element;
	if (pointer != list->tail)
		new_element->next->previous = new_element;
	else
		list->tail = new_element;
}
void InsertBeforePosition(List *list, int value, int position) {
	++list->size;
	Element *pointer = list->head;
	for (int i = 0; i < position; ++i) {
		pointer = pointer->next;
	}
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = value;

	new_element->next = pointer;
	new_element->previous = pointer->previous;
	pointer->previous = new_element;
	if (pointer != list->head)
		new_element->previous->next = new_element;
	else
		list->head = new_element;
}
void GoToHead(List *list, Element *&pointer) {
	pointer = list->head;
}
void GoToTail(List *list, Element *&pointer) {
	pointer = list->tail;
}
void Pointer(Element *pointer) {
	printf("Value of pointed element : %d\n", pointer->value);
}
void MoveToNext(Element *&pointer) {
	pointer = pointer->next;
}
void MoveToPrevious(Element *&pointer) {
	pointer = pointer->previous;
}
void DeleteFromPointer(List *list, Element *&pointer) {
	if (list->head == list->tail) {
		Clear(list);
		pointer = NULL;
	} else {
		Element *tmp = pointer->next;
		if (pointer != list->tail)
			pointer->next->previous = pointer->previous;
		else {
			list->tail = pointer->previous;
			list->tail->next = NULL;
		}
		if (pointer != list->head)
			pointer->previous->next = pointer->next;
		else {
			list->head = pointer->next;
			list->head->previous = NULL;
		}
		free(pointer);
		pointer = tmp;
	}
}
void InsertBeforePointer(List *list, Element *pointer, int value) {
	++list->size;
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = value;

	new_element->next = pointer;
	new_element->previous = pointer->previous;
	new_element->next->previous = new_element;
	if (pointer != list->head)
		new_element->previous->next = new_element;
	else
		list->head = new_element;
}
void InsertAfterPointer(List *list, Element *pointer, int value) {
	++list->size;
	Element *new_element = (Element *)malloc(sizeof(Element));
	new_element->value = value;

	new_element->previous = pointer;
	new_element->next = pointer->next;
	new_element->previous->next = new_element;
	if (pointer != list->tail)
		new_element->next->previous = new_element;
	else
		list->tail = new_element;
}
/*void SizeOfList(List *list) {
	int size = 0;
	for (Element *pointer = list->head; pointer != NULL; pointer = pointer->next)
		++size;
	printf("Size of list : %d\n", size);
}*/
void Help() {
	printf("\n");
	printf("clear : Clear(List *list)\n");
	printf("ah : AddToHead(List *list, int value)\n");
	printf("at : AddToTail(List *list, int value)\n");
	printf("dh : DeleteFromHead(List *list)\n");
	printf("dt : DeleteFromTail(List *list)\n");
	printf("dump : Dump(List *list)\n");
	printf("iap :InsertAfterPosition(List *list, int value, int position)\n");
	printf("ibp :InsertBeforePosition(List *list, int value, int position)\n");
	printf("h : GoToHead(List *list, Element *&pointer)\n");
	printf("t : GoToTail(List *list, Element *&pointer)\n");
	printf("p : Pointer(Element *pointer)\n");
	printf("n : MoveToNext(Element *&pointer)\n");
	printf("pr : MoveToPrevious(Element *&pointer)\n");
	printf("d : DeleteFromPointer(List *list, Element *&pointer)\n");
	printf("ib : InsertBeforePointer(Element *pointer, int value)\n");
	printf("ia : InsertAfterPointer(Element *pointer, int value)\n");
	printf("s : SizeOfList)\n");
	printf("help : Help()\n");
	printf("q : Quit\n");
	printf("\n");
}
bool IsEmpty(List *list) {
	if (list->head == NULL)
		return true;
	else
		return false;
}
