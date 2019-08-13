#include <stdio.h>
#include "Deque.h"
#include "Queue.h"
#include "Stack.h"

int main(void)
{
	// Stack�� ���� �� �ʱ�ȭ ///////
	printf("====== stack ====== \n");
	Stack stack;
	StackInit(&stack);

	// ������ �ֱ� 1�� ///////
	printf("push : ");
	for (int i = 1; i < 6; i++)
	{
		Spush(&stack, i);
		printf("%d ", i);
	}
	printf("\n");

	// Peek
	printf("pop : ");

	// ������ ������ 1�� ///////
	while (!SIsEmpty(&stack))
		printf("%d ", Spop(&stack));

	printf("\n");

	// Queue�� ���� �� �ʱ�ȭ ///////
	printf("====== queue ====== \n");
	Queue queue;
	QueueInit(&queue);

	// ������ �ֱ� 1�� ///////
	printf("enque : ");
	for (int i = 2; i < 12; i+=2)
	{
		Enqueue(&queue, i);
		printf("%d ", i);
	}
	printf("\n");

	// Peek
	printf("deque : ");

	// ������ ������ 1�� ///////
	while (!QIsEmpty(&queue))
		printf("%d ", Dequeue(&queue));

	printf("\n");

	return 0;
}