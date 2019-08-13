#pragma once
#include "Deque.h"

typedef Deque Stack;
void StackInit(Stack* pstack); // ���� �ʱ�ȭ
int SIsEmpty(Stack* pstack); // ������ ������� Ȯ��
void Spush(Stack* pstack, Data data); // ������ push ����
Data Spop(Stack* pstack); // ������ pop ����
Data Speek(Stack* pstack); // ������ peek ����