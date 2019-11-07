#include <windows.h>
#include <stdio.h>

#define MAXCNT 100000000

int g_count = 0;

//�Ӱ迵���� ���� �ʰ� ����ȭ ���� ���� ���·� �����ϸ� ���� �Ҷ����� �ٸ� ����� ��Ÿ���� �ɰ��̴�.
//�� �κ��� �����ϰ� �Ӱ迵���� Ȱ��ȭ�ؼ� ���������� �׻� �ùٸ��� 0�� ����ϴ��� Ȯ���ϰ� �����غ���.

//�ּ� ó���� �κ��� �Ӱ迵�� �ڵ��κ�
CRITICAL_SECTION cs;

DWORD WINAPI MyThread1(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++)
	{
		EnterCriticalSection(&cs);
		g_count += 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

DWORD WINAPI MyThread2(LPVOID arg)
{
	for (int i = 0; i < MAXCNT; i++)
	{
		EnterCriticalSection(&cs);
		g_count -= 2;
		LeaveCriticalSection(&cs);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	//�Ӱ迵�� �ʱ�ȭ
	InitializeCriticalSection(&cs);

	//Thread �� �� ����
	HANDLE hThread[2];
	hThread[0] = CreateThread(NULL, 0, MyThread1, NULL, 0, NULL);
	hThread[1] = CreateThread(NULL, 0, MyThread2, NULL, 0, NULL);

	//Thread �� �� ���� ���
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

	//�Ӱ迵�� ����
	DeleteCriticalSection(&cs);

	//��� ���
	printf("g_count = %d\n", g_count);
	return 0;
}