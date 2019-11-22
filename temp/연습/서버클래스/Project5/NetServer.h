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
		// ��ȯ�� : -1�� �����ϸ� ����, 0���� ũ�� ���� �������� ����
		int recv(SOCKET hClntSock, char msg[BUF_SIZE]);
		int send(SOCKET hClntSock, char msg[BUF_SIZE], int msgSize);

		NetServer();
		virtual ~NetServer();
	};
}