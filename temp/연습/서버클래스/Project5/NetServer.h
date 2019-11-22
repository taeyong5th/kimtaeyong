#pragma once
#include <windows.h>
#include <iostream>
#include <process.h> 

namespace TY
{
	#define BUF_SIZE 1024
	#define MAX_CLNT 256

	class NetServer
	{
	private:
		int clntCnt = 0;
		SOCKET clntSocks[MAX_CLNT];
		HANDLE hMutex;


		WSADATA wsaData;
		SOCKET hServSock;
		SOCKADDR_IN servAdr, clntAdr;	
		HANDLE  hThread;


	public:
		int startUp(int MajorVer, int MinorVer);
		int bind(int portNum);
		int listen();
		SOCKET accept();
		// 반환값 : -1을 리턴하면 오류, 0보다 크면 받은 데이터의 길이
		int recv(SOCKET hClntSock, char msg[BUF_SIZE]);
		int send(SOCKET hClntSock, char msg[BUF_SIZE], int msgSize);

		NetServer();
		virtual ~NetServer();
	};
}