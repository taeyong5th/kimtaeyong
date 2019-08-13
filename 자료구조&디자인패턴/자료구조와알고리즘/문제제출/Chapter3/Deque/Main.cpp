#include <stdio.h>
#include "Deque.h"
#include "Queue.h"
#include "Stack.h"

int main(void)
{
	// Stack의 생성 및 초기화 ///////
	printf("====== stack ====== \n");
	Stack stack;
	StackInit(&stack);

	// 데이터 넣기 1차 ///////
	printf("push : ");
	for (int i = 1; i < 6; i++)
	{
		Spush(&stack, i);
		printf("%d ", i);
	}
	printf("\n");

	// Peek
	printf("pop : ");

	// 데이터 꺼내기 1차 ///////
	while (!SIsEmpty(&stack))
		printf("%d ", Spop(&stack));

	printf("\n");

	// Queue의 생성 및 초기화 ///////
	printf("====== queue ====== \n");
	Queue queue;
	QueueInit(&queue);

	// 데이터 넣기 1차 ///////
	printf("enque : ");
	for (int i = 2; i < 12; i+=2)
	{
		Enqueue(&queue, i);
		printf("%d ", i);
	}
	printf("\n");

	// Peek
	printf("deque : ");

	// 데이터 꺼내기 1차 ///////
	while (!QIsEmpty(&queue))
		printf("%d ", Dequeue(&queue));

	printf("\n");

	return 0;
}