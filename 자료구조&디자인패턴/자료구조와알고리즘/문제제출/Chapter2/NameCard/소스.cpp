#include<iostream>
#include"ArrayList.h"
using namespace std;

void main()
{
	List *plist = new List;
	LData tmp = NULL;
	
	ListInit(plist);

	// 문제2의 조건중 3명의 정보를 받는것을 초기에 입력 받은 수만큼 저장하도록 변경해 보자.
	int count;
	do
	{
		printf("입력할 사람 수 : ");
		scanf("%d", &count);
	} while (count < 0 || count > LIST_LEN);

	char inputName[NAME_LEN];
	char inputPhone[PHONE_LEN];
	for (int i = 0; i < count; i++)
	{
		printf("%d) 이름 : ", i + 1);
		scanf("%s", inputName);
		printf("번호 : ");
		scanf("%s", inputPhone);
		tmp = MakeNameCard(inputName, inputPhone);
		LInsert(plist, tmp);
	}

	// 1. 총 3명의 전화번호 정보를, ArrayList에 저장한다.
	tmp = MakeNameCard("Kim", "010-1234-5678");
	LInsert(plist, tmp);

	tmp = MakeNameCard("Lee", "011-5000-9999");
	LInsert(plist, tmp);

	tmp = MakeNameCard("Gang", "010-5500-7889");
	LInsert(plist, tmp);
	
	// 2. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 출력한다.
	printf("=== Gang 출력 === \n");
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
	
	// 3. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 전화번호 정보를 변경한다.
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

	// 4. 특정 이름을 대상으로 탐색을 진행하여, 그 사람의 정보를 삭제한다.
	name = "Kim";
	LFirst(plist, &tmp);
	do
	{
		if (NameCompare(tmp, name) == 0)
		{
			LRemove(plist);
		}
	} while (LNext(plist, &tmp));

	// 5. 끝으로 남아있는 모든 사람의 전화번호 정보를 출력한다.
	printf("=== 남은 사람 출력 === \n");
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