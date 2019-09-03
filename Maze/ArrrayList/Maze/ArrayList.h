#include "Point.h"
#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__

#define TRUE		1 // '��'�� ǥ���ϱ� ���� ��ũ�� ����
#define FALSE		0 // '����'�� ǥ���ϱ� ���� ��ũ�� ����

#define LIST_LEN	150

typedef Point* LData; // LData�� ���� typedef ���� - int��

typedef struct __ArrayList // �迭��� ����Ʈ�� ������ ����ü
{
	LData arr[LIST_LEN]; // ����Ʈ�� ������� �迭
	int numOfData;		 // ����� �������� ��
	int curPosition;	 // ������ ������ġ�� ���
}ArrayList;

typedef ArrayList List;

void ListInit(List* plist); // �ʱ�ȭ
void LInsert(List* plist, LData data); // ������ ����

int LFirst(List* plist, LData* data); // ù ������ ����
int LNext(List* plist, LData* data); // �� ��° ���� ������ ����

LData LRemove(List* plist); // ������ ������ ����
int LCount(List* plist); // ����� �������� �� ��ȯ

#endif