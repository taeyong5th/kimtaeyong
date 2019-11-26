#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <process.h> 
#include <windows.h>

using namespace std;

#define BUF_SIZE 1024
#define MAX_CLNT 2 // 흑, 백 2명만 접속가능

unsigned WINAPI HandleClnt(void * arg);
void SendMsg(char * msg, int len);
void ErrorHandling(const char * msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

struct OmokData
{
	int playerID; // black인지 white인지
	/*
			request				response		actionid
	0x00		
	0x01 단순 연결 확인			SUCCESS/FAIL	get_isconnected
	0x02 흑백 색깔 배정 요청	black/white		get_playerID
	0x03 (x, y)위치에 돌을 놓음	board정보		get_board

	*/
	int action; // 유저가 어떤 행위를 하는지	
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

	// IP / PORT 초기화
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

		// 접속가능한 클라이언트 수를 2개로 제한
		if (clntCnt < MAX_CLNT)
		{
			WaitForSingleObject(hMutex, INFINITE);
			clntSocks[clntCnt++] = hClntSock;
			ReleaseMutex(hMutex);

			hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		}
		else
		{
			send(hClntSock, "인원이 가득 찼습니다.", sizeof("인원이 가득 찼습니다."), 0);
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
		// recv 반환값이 -1 이면 연결종료
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
