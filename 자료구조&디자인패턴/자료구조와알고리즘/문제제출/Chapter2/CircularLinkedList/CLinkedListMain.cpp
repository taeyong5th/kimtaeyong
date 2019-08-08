#include <stdio.h>
#include "CLinkedList.h"

Data LSearch(List *list, char * name, int day)
{
	Data data;
	int i;
	
	// �̸��� ���� �����͸� ã�´�.
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

	// ��¥��ŭ �̵�
	for (i = 0; i < day % LCount(list); i++)
	{
		LNext(list, &data);
	}

	return data;
}

int main(void)
{
	// ���� ���� ����Ʈ�� ���� �� �ʱ�ȭ ///////
	List list;
	Data data;
	int i;
	ListInit(&list);

	LInsert(&list, createEmployee("Kim", 10001));
	LInsert(&list, createEmployee("Lee", 10002));
	LInsert(&list, createEmployee("Kevin", 10005));
	LInsert(&list, createEmployee("Hwang", 10100));

	printf("======�������� ���� ���=====\n");
	if (LFirst(&list, &data))
	{		
		printEmployee(data);

		for (i = 0; i < LCount(&list) * 3 - 1; i++)
		{
			if (LNext(&list, &data))
				printEmployee(data);
		}
	}

	printf("\n====== Lee�� �������� 2�� �� =====\n");
	data = LSearch(&list, "Lee", 2);
	printEmployee(data);

	printf("\n====== Kevin�� �������� 6�� �� =====\n");
	data = LSearch(&list, "Kevin", 6);
	printEmployee(data);

	return 0;
}