#ifndef FUNCTIONS
#define FUNCTIONS

struct Element {
	int value;
	Element *next;
	Element *previous;
};
struct List {
	Element *head;
	Element *tail;
	int size;
};
void ListInitialisation(List *list);
bool IsEmpty(List *list);

void Clear(List *list); //clear
void AddToHead(List *list, int value); //ah
void AddToTail(List *list, int value); //at
void DeleteFromHead(List *list); //dh
void DeleteFromTail(List *list); //dt
void Dump(List *list); //dump
void InsertAfterPosition(List *list, int value, int position); //iap
void InsertBeforePosition(List *list, int value, int position); //ibp
void GoToHead(List *list, Element *&pointer); //h
void GoToTail(List *list, Element *&pointer); //t
void Pointer(Element *pointer); //p
void MoveToNext(Element *&pointer); //n
void MoveToPrevious(Element *&pointer); //pr
void DeleteFromPointer(List *list, Element *&pointer); //d
void InsertBeforePointer(List *list, Element *pointer, int value); //ib
void InsertAfterPointer(List *list, Element *pointer, int value); //ia
//void SizeOfList(List *list); //s
void Help(); //help

#endif