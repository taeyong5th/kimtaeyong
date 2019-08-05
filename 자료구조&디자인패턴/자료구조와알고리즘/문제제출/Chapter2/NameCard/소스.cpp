#include<iostream>
#include"ArrayList.h"
using namespace std;

void main()
{
	List *plist = new List;
	LData tmp = NULL;
	
	ListInit(plist);

	// ����2�� ������ 3���� ������ �޴°��� �ʱ⿡ �Է� ���� ����ŭ �����ϵ��� ������ ����.
	int count;
	do
	{
		printf("�Է��� ��� �� : ");
		scanf("%d", &count);
	} while (count < 0 || count > LIST_LEN);

	char inputName[NAME_LEN];
	char inputPhone[PHONE_LEN];
	for (int i = 0; i < count; i++)
	{
		printf("%d) �̸� : ", i + 1);
		scanf("%s", inputName);
		printf("��ȣ : ");
		scanf("%s", inputPhone);
		tmp = MakeNameCard(inputName, inputPhone);
		LInsert(plist, tmp);
	}

	// 1. �� 3���� ��ȭ��ȣ ������, ArrayList�� �����Ѵ�.
	tmp = MakeNameCard("Kim", "010-1234-5678");
	LInsert(plist, tmp);

	tmp = MakeNameCard("Lee", "011-5000-9999");
	LInsert(plist, tmp);

	tmp = MakeNameCard("Gang", "010-5500-7889");
	LInsert(plist, tmp);
	
	// 2. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ������ ����Ѵ�.
	printf("=== Gang ��� === \n");
	char* name = "Gang";
	LFirst(plist, &tmp);
	do
	{
		if (NameCompare(tmp, name) == 0)
		{
			ShowNameCardInfo(tmp);
			break;
		}
	} while (LNext(plist, &tmp));
	
	// 3. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ��ȭ��ȣ ������ �����Ѵ�.
	name = "Gang";
	LFirst(plist, &tmp);
	do
	{
		if (NameCompare(tmp, name) == 0)
		{
			ChangePhoneNum(tmp, "010-3333-4445");
			break;
		}
	} while (LNext(plist, &tmp));

	// 4. Ư�� �̸��� ������� Ž���� �����Ͽ�, �� ����� ������ �����Ѵ�.
	name = "Kim";
	LFirst(plist, &tmp);
	do
	{
		if (NameCompare(tmp, name) == 0)
		{
			LRemove(plist);
		}
	} while (LNext(plist, &tmp));

	// 5. ������ �����ִ� ��� ����� ��ȭ��ȣ ������ ����Ѵ�.
	printf("=== ���� ��� ��� === \n");
	LFirst(plist, &tmp);
	do
	{
		ShowNameCardInfo(tmp);
	} while (LNext(plist, &tmp));


	LFirst(plist, &tmp);
	do
	{
		free(tmp);
	} while (LNext(plist, &tmp));	

	delete plist;
}