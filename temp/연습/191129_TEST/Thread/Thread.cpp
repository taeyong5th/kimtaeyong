#include <Windows.h>
#include <stdio.h>
//#include <process.h> //C/C++ ���̺귯���� ����ϴ� Thread ���� ���� �Լ� ����Ҷ� �ʿ�!!

struct Point3D
{
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg)
//unsigned __stdcall MyThread(LPVOID arg) //C/C++ ���̺귯���� ����ϴ� Thread �Լ�
{
	Point3D *pt = (Point3D*)arg;

	//1�ʸ��� ThreadID�� x, y, z�� ȣ���Ѵ�.
	while (1)
	{
		Sleep(1000);
		printf("Running MyThread() %d : %d, %d, %d\n",
			GetCurrentThreadId(), pt->x, pt->y, pt->z);

	}

	//���� �ڵ� ��������
	//ExitThread(0);
	//_endthreadex(0); //C/C++ ���̺귯���� ����ϴ� Thread ���� �Լ�

	return 0;
}

int main(int argc, char* argv[])
{
	//ù ��° Thread ����
	printf("first Thread Created\n");
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	//HANDLE hThread1 = (HANDLE)_beginthreadex(NULL, 0, MyThread, &pt1, 0, NULL); //C/C++ ���̺귯���� ����ϴ� Thread ���� �Լ�

	if (hThread1 == NULL)
		return 1;

	CloseHandle(hThread1);

	//�� ��° Thread ����
	printf("Second Thread Created\n");
	Point3D pt2 = { 40, 50, 60 };
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	//HANDLE hThread2 = (HANDLE)_beginthreadex(NULL, 0, MyThread, &pt2, 0, NULL); //C/C++ ���̺귯���� ����ϴ� Thread ���� �Լ�

	if (hThread2 == NULL)
		return 1;

	CloseHandle(hThread2);

	//Main Thread�� ���ʸ��� ThreadID�� ����Ѵ�.
	while (1)
	{
		printf("Running main() %d\n", GetCurrentThreadId());
		Sleep(1000);
	}

	printf("Main Thread Terminated\n");
	return 0;
}