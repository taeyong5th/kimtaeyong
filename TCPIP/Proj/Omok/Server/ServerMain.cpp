#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <process.h> 
#include <windows.h>
#include "defines.h"

using namespace std;

#define MAX_CLNT 2 // 흑, 백 2명만 접속가능

unsigned WINAPI HandleClnt(void* arg);
void SendMsg(SOCKET* client, char* msg, int len);
void SendMsgAll(char* msg, int len);
void ErrorHandling(const char* msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;

OmokPacketData response;

OmokPoint pointList[BOARD_WIDTH * BOARD_HEIGHT];
int stoneCount = 0;

bool players[2] = {false, false};

int main()
{
	printf("######## SERVER ########\n");
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
	if (bind(hServSock, (SOCKADDR*)& servAdr, sizeof(servAdr)) == SOCKET_ERROR)
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
		hClntSock = accept(hServSock, (SOCKADDR*)& clntAdr, &clntAdrSz);

		if (clntCnt < MAX_CLNT)
		{
			// accept 후 생성된 클라이언트 소켓을 배열에 담음
			WaitForSingleObject(hMutex, INFINITE);
			clntSocks[clntCnt++] = hClntSock;
			ReleaseMutex(hMutex);

			// 각 클라이언트에 대해 thread 생성
			hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)& hClntSock, 0, NULL);
			//WaitForSingleObject(hThread, INFINITE);
		}
		else
		{
			printf("!!");
			send(hClntSock, "full", strlen("full"), 0);
			closesocket(hClntSock);
		}
	}

	CloseHandle(hMutex);
	closesocket(hServSock);
	WSACleanup();

	return 0;
}

unsigned WINAPI HandleClnt(void* arg)
{
	SOCKET hClntSock = *((SOCKET*)arg);
	int strLen = 0, i;
	char msg[BUF_SIZE];
	OmokPacketData* prequest;
	OmokPoint* pPoint;
	int result;	

	while ((strLen = recv(hClntSock, msg, sizeof(msg), 0)) != 0)
	{
		// recv 연결종료		
		if (strLen == SOCKET_ERROR)
		{
			printf("클라이언트 연결이 비정상적으로 종료됨");
			break;
		}
		else if (strLen == 0)
		{
			printf("클라이언트가 정상적으로 종료됨");
			break;
		}
		//printf("%d byte 받음\n", strLen);
		// msg를 읽고 적절한 응답을 보냄
		prequest = (OmokPacketData*)msg;
		switch (prequest->action)
		{
		case OMOK_PLAYER_COLOR:
			printf("GET PLAYER COLOR\n");
			if (players[PLAYER_BLACK] == false)
			{
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				PLAYER_COLOR color = PLAYER_BLACK;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&hClntSock, (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);
				players[PLAYER_BLACK] = true;
			}
			else if (players[PLAYER_WHITE] == false)
			{
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				PLAYER_COLOR color = PLAYER_WHITE;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&hClntSock, (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				players[PLAYER_WHITE] = true;
			}

			// 인원수가 가득차면 전체에게 게임시작 가능하다고 알림
			if (clntCnt == MAX_CLNT)
			{
				response.action = OMOK_IS_STARTABLE;
				response.dataSize = sizeof(int);
				result = TRUE;
				memcpy(&response.data, &result, sizeof(result));
				SendMsgAll((char*)&response, sizeof(int) + sizeof(int) + sizeof(int));

				// 턴에 따라 한쪽은 대기, 한쪽은 플레이
				//SendMsg(&clntSocks[PLAYER_BLACK], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				//SendMsg(&clntSocks[PLAYER_WHITE], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
			}
			break;
		case OMOK_IS_STARTABLE:
		
			break;
		case OMOK_BOARD_STATE:
			printf("GET BOARD INFO\n");
			pPoint = (OmokPoint*)prequest->data;
			printf("%d, %d\n", pPoint->x, pPoint->y);

			pointList[stoneCount].x = pPoint->x;
			pointList[stoneCount].y = pPoint->y;
			++stoneCount;

			response.action = OMOK_BOARD_STATE;
			response.dataSize = sizeof(OmokPoint) * stoneCount;
			memcpy(&response.data, pointList, response.dataSize);
			SendMsgAll((char*)& response, sizeof(int) + sizeof(int) + response.dataSize);

			break;
		default:
			break;
		}

		//SendMsg((SOCKET*)arg, msg, strLen);
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

void SendMsg(SOCKET* client, char* msg, int len)
{
	send(*client, msg, len, 0);
}

void SendMsgAll(char* msg, int len)   // send to all
{
	int i;
	WaitForSingleObject(hMutex, INFINITE);

	for (i = 0; i < clntCnt; i++)
	{
		send(clntSocks[i], msg, len, 0);
	}

	ReleaseMutex(hMutex);
}

void ErrorHandling(const char* msg)
{
	cout << msg << "\n";
	exit(1);
}