#include "NetServer.h"
#include <functional>

//unsigned WINAPI HandleClnt(void * arg);
void SendMsg(char * msg, int len);
void ErrorHandling(const char * msg);


int TY::NetServer::startUp(int MajorVer, int MinorVer)
{
	return WSAStartup(MAKEWORD(MajorVer, MinorVer), &wsaData);
}

int TY::NetServer::bind(int portNum)
{
	// 임계영역설정
	hMutex = CreateMutex(NULL, FALSE, NULL);

	hServSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(portNum);

	return ::bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr));
}

int TY::NetServer::listen()
{
	int errCode = ::listen(hServSock, 5);

	while (1)
	{
		clntAdrSz = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

		// accept 후 생성된 클라이언트 소켓을 배열에 담음
		WaitForSingleObject(hMutex, INFINITE);
		clntSocks[clntCnt++] = hClntSock;
		ReleaseMutex(hMutex);

		hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClnt, (void*)this, 0, NULL);
		//cout << "Connected client IP: " << inet_ntoa(clntAdr.sin_addr) << "\n";
	}

	return errCode;
}

int TY::NetServer::recv()
{
	return 0;
}

int TY::NetServer::send()
{
	return 0;
}


unsigned __stdcall TY::NetServer::HandleClnt(void * arg)
{
	TY::NetServer* p = (TY::NetServer*)arg;

	p->recv();

	return 0;
}

TY::NetServer::NetServer()
{
}

TY::NetServer::~NetServer()
{
}

