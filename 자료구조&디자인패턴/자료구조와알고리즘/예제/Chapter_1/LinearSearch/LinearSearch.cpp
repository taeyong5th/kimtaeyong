#include <iostream>
using namespace std;

int LSearch(int arr[], int len, int target)
{
	for (int i = 0; i < len; i++)
	{
		if (arr[i] == target)
			return i;
	}

	return -1;
}

int main()
{
	int arr[] = { 3, 5, 2, 4, 9 };

	int idx;

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 4);

	if (idx == -1)
		cout << "Å½»ö½ÇÆÐ" << endl;
	else
		cout << "Å¸°Ù ÀúÀå ÀÎµ¦½º : " << idx << endl;

	idx = LSearch(arr, sizeof(arr) / sizeof(int), 7);

	if (idx == -1)
		cout << "Å½»ö½ÇÆÐ" << endl;
	else
		cout << "Å¸°Ù ÀúÀå ÀÎµ¦½º : " << idx << endl;

	return 0;
}