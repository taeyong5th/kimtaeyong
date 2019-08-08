#include <stdio.h>
#include <stdlib.h>
#include "DLinkedList.h"

void ListInit(List * plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}

void FInsert(List * plist, LData data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}

void SInsert(List * plist, LData data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	Node * pred = plist->head;
	newNode->data = data;

	while (pred->next != NULL &&
		plist->comp(data, pred->next->data) != 0)
	{
		pred = pred->next;
	}

	newNode->next = pred->next;
	pred->next = newNode;

	(plist->numOfData)++;
}


void LInsert(List * plist, LData data)
{
	if (plist->comp == NULL) // 정렧기준이 설정되어 있지 않으면..(정렧 기준이 없을 수도 있다.)
		FInsert(plist, data); // 머리에 Node를 추가!
	else
		SInsert(plist, data); // 정렧기준에 근거하여 Node를 추가!
}

int LFirst(List * plist, LData * pdata)
{
	if (plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	if (plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List * plist)
{
	Node * rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}

void SetSortRule(List * plist, int(*comp)(LData d1, LData d2))
{
	plist->comp = comp;
}

void LRemove(List * plist, LData * pdata, int ret)
{
	if (plist->comp == NULL) return;

	Node * before = plist->head;
	Node * remove;

	while (before->next != NULL)
	{
		if (plist->comp(*pdata, before->next->data) == ret)
		{
			remove = before->next;
			before->next = remove->next;
			free(before->next);
			(plist->numOfData)--;
		}
		before = before->next;
	}
}

void Release(List * plist)
{
	if (plist->head == NULL) return;
	Node * before = plist->head;
	Node * remove;

	while (before->next != NULL)
	{
		remove = before->next;
		before->next = remove->next;
		free(remove);
		before = before->next;
	}
	free(plist->head);

	plist->head = NULL;
	plist->comp = NULL;
	plist->numOfData = 0;
}
