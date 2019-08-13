#include "Queue.h"

void QueueInit(Queue * pq)
{
	DequeInit(pq);
}

int QIsEmpty(Queue * pq)
{
	return DQIsEmpty(pq);
}

void Enqueue(Queue * pq, Data data)
{
	DQAddFirst(pq, data);
}

Data Dequeue(Queue * pq)
{
	return DQRemoveLast(pq);
}

Data QPeek(Queue * pq)
{
	return DQGetLast(pq);
}
