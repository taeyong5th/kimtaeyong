#pragma once
#include <windows.h>
#include <iostream>
#include <process.h> 

namespace TY
{
	#define BUF_SIZE 100
	#define MAX_CLNT 256

	class NetServer
	{
	private:
		int clntCnt = 0;
		SOCKET clntSocks[MAX_CLNT];
		HANDLE hMutex;


		WSADATA wsaData;
		SOCKET hServSock, hClntSock;
		SOCKADDR_IN servAdr, clntAdr;
		int clntAdrSz;
		HANDLE  hThread;


	public:
		int startUp(int MajorVer, int MinorVer);
		int bind(int portNum);
		int listen();
		int recv();
		int send();



		static unsigned WINAPI HandleClnt(void * arg);

		NetServer();
		virtual ~NetServer();
	};
}