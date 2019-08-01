#include<stdio.h>

typedef struct _empInfo
{
	int empNum;
	int age;
} EmpInfo;

int main()
{
	EmpInfo empInfoArr[1000];
	EmpInfo e1;
	int eNum;

	printf("사번과 나이 입력:");
	scanf("%d %d", &(e1.empNum), &(e1.age));
	empInfoArr[e1.empNum] = e1;

	printf("확인하고픈 직원의 사번 입력: ");
	scanf("%d", &eNum);

	e1 = empInfoArr[eNum];
	printf("사번 %d, 나이 %d \n", e1.empNum, e1.age);

	return 0;
}