#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <process.h> 
#include <windows.h>
#include "defines.h"

using namespace std;

#define BUF_SIZE 1024
#define MAX_CLNT 2 // ��, �� 2�� ���Ӱ���

unsigned WINAPI HandleClnt(void * arg);
void SendMsg(SOCKET* client, char * msg, int len);
void SendMsgAll(char * msg, int len);
void ErrorHandling(const char * msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

#define GET_ISCONNECTED	0x01
#define GET_PLAYERID	0x02
#define GET_BOARD		0x03

struct OmokRequestData
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
	int dataSize;
	char data[BUF_SIZE];
};

struct OmokResponseData
{
	int action;
	int dataSize;
	char data[BUF_SIZE];
};

struct OmokPoint
{
	int x;
	int y;
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

		// accept �� ������ Ŭ���̾�Ʈ ������ �迭�� ����
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);

		// �� Ŭ���̾�Ʈ�� ���� thread ����
		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)&hClntSock, 0, NULL);
		WaitForSingleObject(hThread, INFINITE);
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
	
	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		// recv ��������		
		if (strLen == SOCKET_ERROR)
		{
			printf("Ŭ���̾�Ʈ ������ ������������ �����");
			break;
		}			
		else if (strLen == 0)
		{
			printf("Ŭ���̾�Ʈ�� ���������� �����");
			break;
		}

		// msg�� �а� ������ ������ ����
		SendMsg((SOCKET*)arg, msg, strLen);
	}
	
	// remove disconnected client
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)   
	{
		if (hClntSock == clntSocks[i])
		{
			clntSocks[i] = NULL;
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

void SendMsg(SOCKET * client, char * msg, int len)
{
	// �޼��� �м�
	OmokRequestData *data = (OmokRequestData*)msg;
	switch (data->action)
	{
	case GET_ISCONNECTED: // 0x01
		break;
	case GET_PLAYERID: // 0x02
		if (clntSocks[PLAYER_ID_BLACK] == *client)
		{
			send(clntSocks[PLAYER_ID_BLACK], msg, len, 0);
		}
		else if (clntSocks[PLAYER_ID_WHITE] == *client)
		{
			send(clntSocks[PLAYER_ID_WHITE], msg, len, 0);
		}
		break;
	case GET_BOARD: // 0x03
		break;
	default:
		break;
	}

}

void SendMsgAll(char * msg, int len)   // send to all
{
	// �޼��� �м�
	OmokRequestData *data = (OmokRequestData*)msg;
	switch (data->action)
	{
	case GET_ISCONNECTED: // 0x01
		break;
	case GET_PLAYERID: // 0x02
		if (clntCnt == 1)
		{

		}
		else if(clntCnt == 2)
		{

		}

		break;
	case GET_BOARD: // 0x03
		break;
	default:
		break;
	}

	int i;
	WaitForSingleObject(hMutex, INFINITE);

	for (i = 0; i < clntCnt; i++)
	{
		send(clntSocks[i], msg, len, 0);
	}

	ReleaseMutex(hMutex);
}

void ErrorHandling(const char * msg)
{
	cout << msg << "\n";
	exit(1);
}