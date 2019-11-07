#include <Windows.h>
#include <stdio.h>

DWORD WINAPI MyThread(LPVOID arg)
{
	while (1);
	return 0;
}

int main()
{
	//CPU ������ �˾Ƴ���.
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	//CPU ������ŭ Thread�� �����Ѵ�.
	for (int i = 0; i < (int)si.dwNumberOfProcessors; i++)
	{
		HANDLE hThread = CreateThread(NULL, 0, MyThread, NULL, 0, NULL);
		
		if (hThread == NULL)
			return 1;

		//�ְ� �켱������ �����Ѵ�.
		SetThreadPriority(hThread, THREAD_PRIORITY_TIME_CRITICAL); //�ش� �ɼǿ� ���� �� �˾ƺ���!!
		CloseHandle(hThread);
	}

	Sleep(1000);

	while (1) 
	{ 
		printf("Main Thread ����!\n");
		break;
	}

	return 0;
}

//int sum = 0;
//
//DWORD WINAPI MyThread(LPVOID arg)
//{
//	int num = (int)arg;
//	
//	for (int i = 1; i <= num; i++)
//		sum += i;
//
//	return 0;
//}
//
//int main()
//{
//	int num = 100;
//
//	HANDLE hThread = CreateThread(NULL, 0, MyThread, (LPVOID)num, CREATE_SUSPENDED, NULL);
//
//	if (hThread == NULL)
//		return 1;
//
//	printf("Thread ���� ��, ��� ��� = %d\n", sum);
//
//	ResumeThread(hThread);
//
//	WaitForSingleObject(hThread, INFINITE);
//
//	printf("Thread ���� ��, ��� ��� = %d\n", sum);
//
//	CloseHandle(hThread);
//
//	return 0;
//}