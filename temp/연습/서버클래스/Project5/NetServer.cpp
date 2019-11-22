#include "NetServer.h"
#include <functional>

int TY::NetServer::startUp(int MajorVer, int MinorVer)
{
	return WSAStartup(MAKEWORD(MajorVer, MinorVer), &wsaData);
}

int TY::NetServer::bind(int portNum)
{
	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(portNum);

	return ::bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
}

int TY::NetServer::listen()
{
	return ::listen(hServSock, 5);
}

SOCKET TY::NetServer::accept()
{
	int clntAdrSz = sizeof(clntAdr);
	SOCKET hClntSock = ::accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

	// accept 후 생성된 클라이언트 소켓을 배열에 담음
	WaitForSingleObject(hMutex, INFINITE);
	clntSocks[clntCnt++] = hClntSock;
	ReleaseMutex(hMutex);

	//hThread = (HANDLE)_beginthreadex(NULL, 0, handleRecv, (void*)&hClntSock, 0, NULL);
	//cout << "Connected client IP: " << inet_ntoa(clntAdr.sin_addr) << "\n";

	return hClntSock;
}

int TY::NetServer::recv(SOCKET hClntSock, char msg[BUF_SIZE])
{
	int length = ::recv(hClntSock, msg, sizeof(msg), 0);
	if (length == SOCKET_ERROR)
	{
		printf("disconnected");

		WaitForSingleObject(hMutex, INFINITE);
		for (int i = 0; i < clntCnt; i++)   // remove disconnected client
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
	}

	return length;
}

int TY::NetServer::send(SOCKET hClntSock, char msg[BUF_SIZE], int msgSize)
{
	return ::send(hClntSock, msg, msgSize, 0);
}

TY::NetServer::NetServer()
{
	hMutex = CreateMutex(NULL, FALSE, NULL);
}

TY::NetServer::~NetServer()
{
	CloseHandle(hMutex);
}
