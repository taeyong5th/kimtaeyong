#include <stdio.h>
#include "CLinkedList.h"

Data LSearch(List *list, char * name, int day)
{
	Data data;
	int i;
	
	// 이름과 같은 데이터를 찾는다.
	if (LFirst(list, &data))
	{
		if (strcmp(data->name, name) != 0)
		{
			for (i = 0; i < LCount(list) - 1; i++)
			{
				if (LNext(list, &data))
				{
					if (strcmp(data->name, name) == 0)
					{
						break;
					}
				}
			}
		}
	}

	// 날짜만큼 이동
	for (i = 0; i < day % LCount(list); i++)
	{
		LNext(list, &data);
	}

	return data;
}

int main(void)
{
	// 원형 연결 리스트의 생성 및 초기화 ///////
	List list;
	Data data;
	int i;
	ListInit(&list);

	LInsert(&list, createEmployee("Kim", 10001));
	LInsert(&list, createEmployee("Lee", 10002));
	LInsert(&list, createEmployee("Kevin", 10005));
	LInsert(&list, createEmployee("Hwang", 10100));

	printf("======당직서기 세번 출력=====\n");
	if (LFirst(&list, &data))
	{		
		printEmployee(data);

		for (i = 0; i < LCount(&list) * 3 - 1; i++)
		{
			if (LNext(&list, &data))
				printEmployee(data);
		}
	}

	printf("\n====== Lee가 당직선후 2일 뒤 =====\n");
	data = LSearch(&list, "Lee", 2);
	printEmployee(data);

	printf("\n====== Kevin이 당직선후 6일 뒤 =====\n");
	data = LSearch(&list, "Kevin", 6);
	printEmployee(data);

	return 0;
}