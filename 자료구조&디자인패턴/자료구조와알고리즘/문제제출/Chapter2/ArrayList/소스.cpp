#include<iostream>
#include"ArrayList.h"
using namespace std;

void main()
{
	List *plist = new List;
	LData *tmp = new int;
	int iSum = 0;

	ListInit(plist);

	for (int i = 0; i < 50; i++)
	{
		if (i % 2 == 1)
		{
			LInsert(plist, i);
		}		
	}
	
	LFirst(plist, tmp);
	do
	{
		iSum += *tmp;
	} while (LNext(plist, tmp));
	
	cout << "iSum = " << iSum << endl;

	LFirst(plist, tmp);
	do
	{
		if (*tmp % 5 == 0) LRemove(plist);
	} while (LNext(plist, tmp));

	LFirst(plist, tmp);
	do
	{
		cout << "List[" << plist->curPosition << "] = " << *tmp << endl;
	} while (LNext(plist, tmp));

	delete plist;
	delete tmp;
}