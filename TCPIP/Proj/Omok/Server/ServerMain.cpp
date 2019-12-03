#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <process.h> 
#include <windows.h>
#include "defines.h"

using namespace std;

#define MAX_CLNT 2 // ��, �� 2�� ���Ӱ���

unsigned WINAPI HandleClnt(void* arg);
void SendMsg(SOCKET* client, char* msg, int len);
void SendMsgAll(char* msg, int len);
void ErrorHandling(const char* msg);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT] = {NULL, NULL};
HANDLE hMutex;

OmokPacketData response;

OmokPoint pointList[BOARD_WIDTH * BOARD_HEIGHT];
int stoneCount = 0;
int playerTurn = PLAYER_BLACK;

bool isReady[2] = {false, false};

int testvalue = 0;

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

	// IP / PORT �ʱ�ȭ
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
			// accept �� ������ Ŭ���̾�Ʈ ������ �迭�� ����
			WaitForSingleObject(hMutex, INFINITE);
			clntSocks[clntCnt++] = hClntSock;
			ReleaseMutex(hMutex);

			// �� Ŭ���̾�Ʈ�� ���� thread ����
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
	PLAYER_COLOR color;
	int result;

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
		//printf("%d byte ����\n", strLen);
		// msg�� �а� ������ ������ ����
		prequest = (OmokPacketData*)msg;
		switch (prequest->action)
		{
		case OMOK_PLAYER_COLOR:
			printf("GET PLAYER COLOR\n");
			if (hClntSock == clntSocks[PLAYER_BLACK])
			{
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				PLAYER_COLOR color = PLAYER_BLACK;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&hClntSock, (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);
				//isReady[PLAYER_BLACK] = true;
				printf("black\n");
			}
			else if (hClntSock == clntSocks[PLAYER_WHITE])
			{
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				PLAYER_COLOR color = PLAYER_WHITE;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&hClntSock, (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				//isReady[PLAYER_WHITE] = true;
				printf("white\n");
			}
			break;
		case OMOK_IS_STARTABLE:
			if (hClntSock == clntSocks[PLAYER_BLACK])
			{
				isReady[PLAYER_BLACK] = true;
				printf("black is ready\n");
			}
			else if (hClntSock == clntSocks[PLAYER_WHITE])
			{
				isReady[PLAYER_WHITE] = true;
				printf("white is ready\n");
			}

			// ���ʴ� ������ �غ� �Ǹ� ���۰����ϴٰ� �˸�
			if (isReady[PLAYER_BLACK] && isReady[PLAYER_WHITE])
			{
				result = TRUE;
			}
			else
			{
				result = FALSE;
			}
			response.action = OMOK_IS_STARTABLE;
			response.dataSize = sizeof(int);
			memcpy(&response.data, &result, sizeof(result));
			SendMsgAll((char*)&response, sizeof(int) + sizeof(int) + response.dataSize);
						
			// �Ͽ� ���� ������ ���, ������ �÷��� 
			if (isReady[PLAYER_BLACK] && isReady[PLAYER_WHITE])
			{
				// ���� ���� ����
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				color = PLAYER_BLACK;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&clntSocks[PLAYER_BLACK], (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);

				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				color = PLAYER_WHITE;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&clntSocks[PLAYER_WHITE], (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);

				response.dataSize = 0;
				response.action = OMOK_PLAY;
				SendMsg(&clntSocks[PLAYER_BLACK], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				response.action = OMOK_WAIT;
				SendMsg(&clntSocks[PLAYER_WHITE], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				printf("game start\n");
			}
			break;
		case OMOK_PUT_STONE:
			printf("PUT STONE : ");
			pPoint = (OmokPoint*)prequest->data;
			printf("%d, %d\n", pPoint->x, pPoint->y);

			pointList[stoneCount].x = pPoint->x;
			pointList[stoneCount].y = pPoint->y;
			pointList[stoneCount].color = pPoint->color;
			++stoneCount;

			response.action = OMOK_BOARD_STATE;
			response.dataSize = sizeof(OmokPoint) * stoneCount;
			memcpy(&response.data, pointList, response.dataSize);
			SendMsgAll((char*)& response, sizeof(int) + sizeof(int) + response.dataSize);

			// �Ͽ� ���� ������ ���, ������ �÷���
			if (hClntSock == clntSocks[PLAYER_BLACK])
			{
				response.dataSize = 0;
				response.action = OMOK_WAIT;
				SendMsg(&clntSocks[PLAYER_BLACK], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				response.action = OMOK_PLAY;
				SendMsg(&clntSocks[PLAYER_WHITE], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
			}
			else
			{
				response.dataSize = 0;
				response.action = OMOK_PLAY;
				SendMsg(&clntSocks[PLAYER_BLACK], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				response.action = OMOK_WAIT;
				SendMsg(&clntSocks[PLAYER_WHITE], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
			}			
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
			isReady[i] = false;
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