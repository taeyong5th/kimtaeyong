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
int checkTurn(SOCKET* socket);
int isWin(int x, int y, int player);

int clntCnt = 0;
SOCKET clntSocks[MAX_CLNT] = { NULL, NULL };
HANDLE hMutex;

OmokPacketData response;

OmokPoint pointList[BOARD_WIDTH * BOARD_HEIGHT];
int board[BOARD_WIDTH][BOARD_HEIGHT];
int stoneCount = 0;
int playerTurn = PLAYER_BLACK;

bool isReady[2] = { false, false };

int testvalue = 0;

int main()
{

	// 오목판 초기화
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(board[i], PLAYER_NONE, sizeof(int) * BOARD_HEIGHT);
	}

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

			printf("connected socket %d\n", hClntSock);

			// 각 클라이언트에 대해 thread 생성
			hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)& hClntSock, 0, NULL);
			//WaitForSingleObject(hThread, INFINITE);			
		}
		else
		{
			printf("!!");
			//response.action = OMOK_PLAYER_FULL;
			//response.dataSize = 0;
			//SendMsg(&hClntSock, (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);
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
		// recv 연결종료		
		if (strLen == SOCKET_ERROR)
		{
			printf("클라이언트 연결이 비정상적으로 종료됨\n");
			break;
		}
		else if (strLen == 0)
		{
			printf("클라이언트가 정상적으로 종료됨\n");
			break;
		}

		//printf("%d byte 받음\n", strLen);
		// msg를 읽고 적절한 응답을 보냄
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
				printf("send color info : black\n");
			}
			else if (hClntSock == clntSocks[PLAYER_WHITE])
			{
				response.action = OMOK_PLAYER_COLOR;
				response.dataSize = sizeof(PLAYER_COLOR);
				PLAYER_COLOR color = PLAYER_WHITE;
				memcpy(&response.data, &color, response.dataSize);
				SendMsg(&hClntSock, (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
				//isReady[PLAYER_WHITE] = true;
				printf("send color info : white %d\n");
			}
			break;
		case OMOK_STARTABLE:
			printf("ready request : ");
			if (hClntSock == clntSocks[PLAYER_BLACK])
			{
				isReady[PLAYER_BLACK] = true;
				printf("black is ready %d %d\n", hClntSock, clntSocks[0]);
			}
			else if (hClntSock == clntSocks[PLAYER_WHITE])
			{
				isReady[PLAYER_WHITE] = true;
				printf("white is ready %d %d\n", hClntSock, clntSocks[1]);
			}

			// 턴에 따라 한쪽은 대기, 한쪽은 플레이 
			if (isReady[PLAYER_BLACK] && isReady[PLAYER_WHITE])
			{
				// 색상 지정 해줌
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
		case OMOK_IS_MYTURN:
			result = checkTurn(&hClntSock);
			response.action = OMOK_STARTABLE;
			response.dataSize = sizeof(int);
			memcpy(&response.data, &result, sizeof(result));
			SendMsg(&hClntSock, (char*)&response, sizeof(int) + sizeof(int) + response.dataSize);
			break;
		case OMOK_PUT_STONE:
			printf("PUT STONE : ");
			pPoint = (OmokPoint*)prequest->data;
			printf("%d, %d\n", pPoint->x, pPoint->y);

			pointList[stoneCount].x = pPoint->x;
			pointList[stoneCount].y = pPoint->y;
			pointList[stoneCount].color = pPoint->color;
			++stoneCount;

			board[pPoint->x][pPoint->y] = pPoint->color;

			response.action = OMOK_BOARD_STATE;
			response.dataSize = sizeof(OmokPoint) * stoneCount;
			memcpy(&response.data, pointList, response.dataSize);
			SendMsgAll((char*)& response, sizeof(int) + sizeof(int) + response.dataSize);

			result = isWin(pPoint->x, pPoint->y, pPoint->color);
			if (result == FALSE)
			{
				// 턴에 따라 한쪽은 대기, 한쪽은 플레이
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
			}
			else
			{
				response.dataSize = sizeof(int);
				response.action = OMOK_IS_WIN;

				result = true;
				memcpy(&response.data, &result, sizeof(result));
				SendMsg(&clntSocks[pPoint->color], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);

				result = false;
				memcpy(&response.data, &result, sizeof(result));
				SendMsg(&clntSocks[(pPoint->color + 1) % 2], (char*)& response, sizeof(int) + sizeof(int) + response.dataSize);

				// 오목판 초기화
				for (int i = 0; i < BOARD_WIDTH; ++i)
				{
					memset(board[i], PLAYER_NONE, sizeof(int) * BOARD_HEIGHT);
				}
				stoneCount = 0;
				playerTurn = PLAYER_BLACK;
				isReady[PLAYER_BLACK] = false;
				isReady[PLAYER_WHITE] = false;
			}
			break;
		default:
			break;
		}

		//SendMsg((SOCKET*)arg, msg, strLen);
	}


	if (isReady[PLAYER_BLACK] && isReady[PLAYER_WHITE])
	{
		printf("연결 끊김으로 인한 초기화\n");
		response.dataSize = 0;
		response.action = OMOK_DISCONNECTED;
		SendMsgAll((char*)& response, sizeof(int) + sizeof(int) + response.dataSize);
		// 오목판 초기화
		for (int i = 0; i < BOARD_WIDTH; ++i)
		{
			memset(board[i], PLAYER_NONE, sizeof(int) * BOARD_HEIGHT);
		}
		stoneCount = 0;
		playerTurn = PLAYER_BLACK;
		isReady[PLAYER_BLACK] = false;
		isReady[PLAYER_WHITE] = false;
	}

	// remove disconnected client
	WaitForSingleObject(hMutex, INFINITE);
	for (i = 0; i < clntCnt; i++)
	{
		if (hClntSock == clntSocks[i])
		{
			//printf("[%d] %d 가 나갔음\n", i, clntSocks[i]);
			//clntSocks[i] = NULL;
			isReady[i] = false;
			while (i < clntCnt - 1)
			{
				clntSocks[i] = clntSocks[i + 1];
				isReady[i] = isReady[i + 1];
				i++;
				printf("연결 끊김으로 인해 WHITE -> BLACK 변경\n");
			}
			break;
		}
	}
	clntCnt--;
	ReleaseMutex(hMutex);

	closesocket(hClntSock);
	//printf("Socket Count = %d \n", clntCnt);
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

int checkTurn(SOCKET* socket)
{
	if (playerTurn == PLAYER_BLACK && *socket == clntSocks[PLAYER_BLACK])
	{
		return TRUE;
	}
	else if (playerTurn == PLAYER_WHITE && *socket == clntSocks[PLAYER_WHITE])
	{
		return TRUE;
	}

	return FALSE;
}

int isWin(int x, int y, int player)
{
	int count = 1;
	const int maxCount = 2;
	// (x, y)에서 가로 체크
	for (int i = x - 1; i >= 0; --i)
	{
		if (player == board[i][y])
		{
			++count;
		}
		else
		{
			break;
		}
	}
	for (int i = x + 1; i < BOARD_WIDTH; ++i)
	{
		if (player == board[i][y])
		{
			++count;
		}
		else
		{
			break;
		}
	}
	if (count == maxCount)
		return TRUE;

	// 세로 체크
	count = 1;
	for (int i = y - 1; i >= 0; --i)
	{
		if (player == board[x][i])
			++count;
		else
			break;
	}
	for (int i = y + 1; i < BOARD_HEIGHT; ++i)
	{
		if (player == board[x][i])
			++count;
		else
			break;
	}
	if (count == maxCount)
		return TRUE;

	// 대각선 체크
	count = 1;
	for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; --i, --j)
	{
		if (player == board[i][j])
			++count;
		else
			break;
	}
	for (int i = x + 1, j = y + 1; i < BOARD_WIDTH && j < BOARD_HEIGHT; ++i, ++j)
	{
		if (player == board[i][j])
			++count;
		else
			break;
	}
	if (count == maxCount)
		return TRUE;

	// 대각선 체크 2
	count = 1;
	for (int i = x - 1, j = y + 1; i >= 0 && j < BOARD_HEIGHT; --i, ++j)
	{
		if (player == board[i][j])
			++count;
		else
			break;
	}
	for (int i = x + 1, j = y - 1; i < BOARD_WIDTH && j >= 0; ++i, --j)
	{
		if (player == board[i][j])
			++count;
		else
			break;
	}
	if (count == maxCount)
		return TRUE;


	return FALSE;
}
