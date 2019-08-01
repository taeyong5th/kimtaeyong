#include <iostream>
using namespace std;

void HanoiTowerMove(int num, char from, char by, char to)
{
	if (num == 1)    // 이동할 원반의 수가 1개라면
	{
		cout << "원반1을 " << from << "에서 " << to << "로 이동" << endl;
	}
	else
	{
		HanoiTowerMove(num - 1, from, to, by);    // 3단계 중 1단계
		cout << "원반" << num <<"을(를) " << from << "에서 " << to << "로 이동" << endl;  // 3단계 중 2단계
		HanoiTowerMove(num - 1, by, from, to);    // 3단계 중 3단계
	}
}


int main(void)
{
	// 막대A의 원반 3개를 막대B를 경유하여 막대C로 옮기기
	HanoiTowerMove(3, 'A', 'B', 'C');
	return 0;
}