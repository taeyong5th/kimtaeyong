#pragma once
#include "Deque.h"

typedef Deque Stack;
void StackInit(Stack* pstack); // 스택 초기화
int SIsEmpty(Stack* pstack); // 스택이 비었는지 확인
void Spush(Stack* pstack, Data data); // 스택의 push 연산
Data Spop(Stack* pstack); // 스택의 pop 연산
Data Speek(Stack* pstack); // 스택의 peek 연산