#include <stdio.h>
#include <string.h>
#include "PriorityQueue.h"

int DataPriorityComp(const char* ch1, const char* ch2)
{
	return strlen(ch2) - strlen(ch1);
}

int main(void)
{
	PQueue pq;
	PQueueInit(&pq, DataPriorityComp);

	PEnqueue(&pq, "ABCDE");
	PEnqueue(&pq, "ABC");
	PEnqueue(&pq, "ABCDEFG");
	PEnqueue(&pq, "ABCDEFGHIJ");
	PEnqueue(&pq, "ABCD");
	printf("%s \n", PDequeue(&pq));


	while (!PQIsEmpty(&pq))
		printf("%s \n", PDequeue(&pq));

	return 0;
}
