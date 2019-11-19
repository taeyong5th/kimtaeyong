#pragma once
#include "GlobalDefine.h"
#include "GlobalFunction.h"

#define BUF_SIZE 100

int g_iClientCount = 0;
SOCKET g_ClientSockets[MAX_CLNT];
HANDLE g_hMutex;

unsigned WINAPI HandleClnt(void * arg);
void SendMsg(char * msg, int len);

int main()
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	SOCKADDR_IN servAdr, clntAdr;
	int clntAdrSz;
	HANDLE  hThread;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		err_quit("startup error");
	}

	g_hMutex = CreateMutex(NULL, FALSE, NULL);
	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(PORT_NUMBER);

	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		err_quit("bind() error");
	}

	// listen
	if (listen(hServSock, SOMAXCONN) == SOCKET_ERROR)
	{
		err_quit("listen() error");
	}

	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		// accept 후 생성된 클라이언트 소켓을 배열에 담음
		WaitForSingleObject(g_hMutex, INFINITE);
		g_ClientSockets[g_iClientCount++] = hClntSock;
		ReleaseMutex(g_hMutex);

		// 소켓마다 각 스레드 생성
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);

		//cout << "Connected client IP: " << inet_ntoa(clntAdr.sin_addr) << "\n";
	}

	closesocket(hServSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI HandleClnt(void * arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];

	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		printf("len = %d \n", strLen);
		if (strLen == -1)
			break;

		SendMsg(msg, strLen);
	}

	WaitForSingleObject(g_hMutex, INFINITE);

	for (i = 0; i < g_iClientCount; i++)   // remove disconnected client
	{
		if (hClntSock == g_ClientSockets[i])
		{
			while (i++ < g_iClientCount - 1)
			{
				g_ClientSockets[i] = g_ClientSockets[i + 1];
			}
			break;
		}
	}

	g_iClientCount--;
	ReleaseMutex(g_hMutex);
	closesocket(hClntSock);
	printf("Socket Count = %d \n", g_iClientCount);
	return 0;

	return 0;
}

void SendMsg(char * msg, int len)
{
}

