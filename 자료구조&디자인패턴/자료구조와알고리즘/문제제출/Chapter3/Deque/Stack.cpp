#include "Stack.h"

void StackInit(Stack * pstack)
{
	DequeInit(pstack);
}

int SIsEmpty(Stack * pstack)
{
	return DQIsEmpty(pstack);
}

void Spush(Stack * pstack, Data data)
{
	DQAddLast(pstack, data);
}

Data Spop(Stack * pstack)
{
	return DQRemoveLast(pstack);
}

Data Speek(Stack * pstack)
{
	return DQGetLast(pstack);
}
