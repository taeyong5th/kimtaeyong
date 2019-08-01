#include <iostream>
#include<algorithm>
using namespace std;

int BinarySearch(int ar[], int first, int last, int target, int &opCount)
{
	if (first > last) return -1;

	int mid;

	opCount++;
	mid = (first + last) / 2;
	if (target == ar[mid])
	{
		return mid;
	}
	else
	{
		if (target > ar[mid])
			first = mid + 1;
		else
			last = mid - 1;
		BinarySearch(ar, first, last, target, opCount);
	}
}

int BSearch(int ar[], int len, int target)
{
	int first = 0;
	int last = len - 1;
	
	int opCount = 0;   // 비교연산의 횟수를 기록

	int find = BinarySearch(ar, first, last, target, opCount);

	cout << "비교연산 횟수: " << opCount << endl;  // 탐색 실패 시 연산횟수 출력
	return find;
}

int main(void)
{
	int arr1[500] = { 0, };    // 모든 요소 0으로 초기화
	int arr2[5000] = { 0, };    // 모든 요소 0으로 초기화
	int arr3[50000] = { 0, };    // 모든 요소 0으로 초기화
	int idx;

	arr1[380] = 1;

	sort(arr1, arr1 + 500);

	// 저장되지 않은 정수 1을 찾으라고 명령
	idx = BSearch(arr1, sizeof(arr1) / sizeof(int), 1);

	if (idx == -1)
		cout << "탐색 실패 " << endl << endl;
	else
		cout << "타겟 저장 인덱스: " << idx << endl << endl;

	// 저장되지 않은 정수 2를 찾으라고 명령
	idx = BSearch(arr2, sizeof(arr2) / sizeof(int), 2);

	if (idx == -1)
		cout << "탐색 실패" << endl << endl;
	else
		cout << "타겟 저장 인덱스: " << idx << endl << endl;

	// 저장되지 않은 정수 3을 찾으라고 명령
	idx = BSearch(arr3, sizeof(arr3) / sizeof(int), 3);

	if (idx == -1)
		cout << "탐색 실패 " << endl << endl;
	else
		cout << "타겟 저장 인덱스: " << idx << endl << endl;

	return 0;
}