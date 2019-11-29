#include <iostream>
#include <windows.h>
#include <process.h> 
#include "defines.h"

using namespace std;

#define NAME_SIZE 20

unsigned WINAPI SendMsg(void * arg);
unsigned WINAPI RecvMsg(void * arg);
void ErrorHandling(const char * msg);

char name[NAME_SIZE] = "[DEFAULT]";
char msg[BUF_SIZE];
int action;

GAME_STATE state;
OmokPacketData request;
int m_aBoard[BOARD_WIDTH][BOARD_HEIGHT];

int main()
{
	printf("######## CLIENT ########\n");
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(m_aBoard[i], PLAYER_ID_NONE, sizeof(int) * BOARD_HEIGHT);
	}

	state = GAME_STATE_START_WAIT;

	WSADATA wsaData;
	SOCKET hSock;
	SOCKADDR_IN servAdr;
	HANDLE hSndThread, hRcvThread;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		ErrorHandling("WSAStartup() error!");
	}

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(9000);

	if (connect(hSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
	{
		ErrorHandling("connect() error");
	}

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)&hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)&hSock, 0, NULL);

	WaitForSingleObject(hSndThread, INFINITE);
	WaitForSingleObject(hRcvThread, INFINITE);
	closesocket(hSock);
	WSACleanup();
	return 0;
}

unsigned WINAPI SendMsg(void * arg)   // send thread main
{
	SOCKET hSock = *((SOCKET*)arg);
	char nameMsg[NAME_SIZE + BUF_SIZE];
	
	while (1)
	{
		cin >> action;

		/*if (msg[0] == 'q')
		{
			printf("QUIT!");
			Sleep(1000);
			closesocket(hSock);
			exit(0);
		}
		if (!strcmp(msg, "q\n") || !strcmp(msg, "Q\n"))
		{
			printf("QUIT!");
			Sleep(1000);
			closesocket(hSock);
			exit(0);
		}*/
		OmokPoint point;
		switch (action)
		{
		case 1: // 플레이어 팀 색깔(돌 색깔) 얻기
			request.action = GET_PLAYERID;
			send(hSock, (char*)&request, sizeof(int) + sizeof(int), 0);
			break;
		case 2:
			cin >> point.x >> point.y;
			// 돌을 놓음
			request.action = GET_BOARD;
			memcpy(&request.data, &point, sizeof(point));
			send(hSock, (char*)&request, sizeof(int) + sizeof(int) + sizeof(OmokPoint), 0);

			//send(hSock, (char*)&point, sizeof(point), 0);
			break;
		default:
			break;
		}

		//sprintf(nameMsg, "%s", msg);
		//send(hSock, nameMsg, strlen(nameMsg), 0);
	}

	return 0;
}

unsigned WINAPI RecvMsg(void * arg)   // read thread main
{
	int hSock = *((SOCKET*)arg);
	char packet[NAME_SIZE + BUF_SIZE];
	int dataSize;
	OmokPacketData* prequest;
	OmokPoint* pointlist;
	while (1)
	{
		dataSize = recv(hSock, packet, NAME_SIZE + BUF_SIZE - 1, 0);

		if (dataSize == -1)
		{
			cout << "소켓 에러 종료" << endl;
			return -1;
		}
		else if (dataSize == 0)
		{
			cout << "정상적인 종료" << endl;
			return 0;
		}
		prequest = (OmokPacketData*)packet;

		switch (prequest->action)
		{
		case GET_BOARD:
			cout << "보드 정보 날라옴" << endl;
			
			pointlist = (OmokPoint*)prequest->data;
			for (int i = 0; i < prequest->dataSize / sizeof(OmokPoint); ++i)
			{
				cout << pointlist[i].x << ", " << pointlist[i].y << endl;				
			}

			break;
		default:
			break;
		}

	}

	return 0;
}

void ErrorHandling(const char *msg)
{
	cout << msg << "\n";
	exit(1);
}
