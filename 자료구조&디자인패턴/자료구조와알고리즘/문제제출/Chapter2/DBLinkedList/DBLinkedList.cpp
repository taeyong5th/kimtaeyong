#include <stdio.h>
#include <stdlib.h>
#include "DBLinkedList.h"

void ListInit(List * plist)
{
	plist->head = NULL;
	plist->tail = NULL;
	plist->numOfData = 0;

	Node * headDummy = (Node*)malloc(sizeof(Node));
	Node * tailDummy = (Node*)malloc(sizeof(Node));

	headDummy->prev = NULL;
	headDummy->next = tailDummy;
	tailDummy->prev = headDummy;
	tailDummy->next = NULL;

	plist->head = headDummy;
	plist->tail = tailDummy;
	/*
	리스트 초기화 후 상태
	            head          tail
	             ↓            ↓
	NULL <- headDummy <-> tailDummy -> NULL
	*/
}

void LInsert(List * plist, Data data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;
	
	newNode->next = plist->tail;
	newNode->prev = plist->tail->prev;

	plist->tail->prev->next = newNode;
	plist->tail->prev = newNode;
	
	(plist->numOfData)++;
}

int LFirst(List * plist, Data * pdata)
{
	if (plist->head->next == plist->tail)
		return FALSE;

	plist->cur = plist->head->next;
	*pdata = plist->cur->data;

	return TRUE;
}

int LNext(List * plist, Data * pdata)
{
	if (plist->cur->next == plist->tail)
		return FALSE;

	plist->cur = plist->cur->next;
	*pdata = plist->cur->data;

	return TRUE;
}

Data LRemove(List * plist)
{
	Data data = plist->cur->data;
	Node * prev = plist->cur->prev;

	plist->cur->prev->next = plist->cur->next;
	plist->cur->next->prev = plist->cur->prev;

	free(plist->cur);
	plist->cur = prev;
	return data;
}

int LCount(List * plist)
{
	return plist->numOfData;
}