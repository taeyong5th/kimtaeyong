#include <iostream>

using namespace std;

int BSearchRecursive(int arr[], int first, int last, int target)
{
	if (first > last) return -1;

	int mid = (first + last) / 2;	
	if (target == arr[mid])
	{
		return mid;
	}
	else if (target < arr[mid])
	{
		return BSearchRecursive(arr, first, mid - 1, target);
	}
	else
	{
		return BSearchRecursive(arr, mid + 1, last, target);
	}
}

int BSearch(int arr[], int len, int target)
{
	int first = 0; // 탐색대상의 시작 인덱스
	int last = len - 1; // 탐색 대상의 마지막 인덱스
	int mid;	while (first <= last)
	{
		mid = (first + last) / 2; // 1번 과정
		if(target == arr[mid]) // 2번 과정
		{
			return mid;
		}
		else
		{
			if (target < arr[mid]) // 2번 과정
				last = mid - 1; // 3번 과정
			else
				first = mid + 1; // 3번 과정
		}
	}
	return -1;
}

int main()
{
	int arr[10] = {1, 2, 4, 8, 15, 23, 34, 45, 55, 70};

	cout << BSearchRecursive(arr, 0, 9, 4) << endl; // 3
	cout << BSearchRecursive(arr, 0, 9, 34) << endl; // 6
	cout << BSearchRecursive(arr, 0, 9, 35) << endl; // -1

	return 0;
}

