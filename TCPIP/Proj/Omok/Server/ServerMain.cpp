#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <process.h> 
#include <windows.h>

using namespace std;

#define BUF_SIZE 1024
#define MAX_CLNT 2 // ��, �� 2�� ���Ӱ���

unsigned WINAPI HandleClnt(void * arg);
void SendMsg(char * msg, int len);
void ErrorHandling(const char * msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

struct OmokData
{
	int playerID; // black���� white����
	/*
			request				response		actionid
	0x00		
	0x01 �ܼ� ���� Ȯ��			SUCCESS/FAIL	get_isconnected
	0x02 ��� ���� ���� ��û	black/white		get_playerID
	0x03 (x, y)��ġ�� ���� ����	board����		get_board

	*/
	int action; // ������ � ������ �ϴ���	
	int size; 
	char data[BUF_SIZE];
};

struct MyPacket
{
	unsigned int bytelength;
	unsigned int data[];
};

int main()
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE  hThread;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}
	hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	// IP / PORT �ʱ�ȭ
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(9000);

	// bind
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("bind() error");
	}

	// listen
	if (listen(hServSock, SOMAXCONN) == SOCKET_ERROR)
	{
		ErrorHandling("listen() error");
	}

	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		// ���Ӱ����� Ŭ���̾�Ʈ ���� 2���� ����
		if (clntCnt < MAX_CLNT)
		{
			WaitForSingleObject(hMutex, INFINITE);
			clntSocks[clntCnt++] = hClntSock;
			ReleaseMutex(hMutex);

			hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		}
		else
		{
			send(hClntSock, "�ο��� ���� á���ϴ�.", sizeof("�ο��� ���� á���ϴ�."), 0);
			closesocket(hClntSock);
		}
	}

	CloseHandle(hMutex);
	closesocket(hServSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI HandleClnt(void * arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];
	int st_test;

	while ((strLen = recv(hClntSock, (char*)(&st_test), sizeof(st_test), 0)) != 0)
	{
		// recv ��ȯ���� -1 �̸� ��������
		if (strLen == SOCKET_ERROR)
			break;

		SendMsg((char*)(&st_test), strLen);
	}
	
	// remove disconnected client
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)   
	{
		if (hClntSock == clntSocks[i])
		{
			while (i++ < clntCnt - 1)
			{
				clntSocks[i] = clntSocks[i + 1];
			}
			break;
		}
	}
	clntCnt--;
	ReleaseMutex(hMutex);

	closesocket(hClntSock);
	printf("Socket Count = %d \n", clntCnt);
	return 0;
}

void SendMsg(char * msg, int len)
{

}

void ErrorHandling(const char * msg)
{


}
