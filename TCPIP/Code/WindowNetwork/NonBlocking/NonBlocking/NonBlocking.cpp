#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define SERVERIP	"127.0.0.1" // ���� �ӽ��� IP�ּ�
#define SERVERPORT	9000
#define BUFSIZE		512

// ���� �Լ� ���� ��� �� ����
void err_quit(const char* msg);
// ���� �Լ� ���� ���
void err_display(const char* msg);

int main()
{
	int retval;

	//���� �ʱ�ȭ
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");
	
	//�ͺ��ŷ �������� ��ȯ
	u_long on = 1;
	retval = ioctlsocket(listen_sock, FIONBIO, &on);

	if (retval == SOCKET_ERROR)
		err_quit("ioctlsocket()");

	//bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);
	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
		err_quit("bind()");

	//listen()
	retval = listen(listen_sock, SOMAXCONN);

	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	//������ ��ſ� ����� ����
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen;
	char buf[BUFSIZE + 1];

	while (1)
	{
		//accept()
	ACCEPT_AGAIN:
		addrlen = sizeof(clientaddr);
		client_sock = accept(listen_sock, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			//������(�� �����ϱ� GOTO, �Լ��� ó���Ұ�쿣 ��� �õ���, ��� ���� �� �ƿ��ǰ� ������!!)
			if (WSAGetLastError() == WSAEWOULDBLOCK)
				goto ACCEPT_AGAIN;

			err_display("accept()");
			break;
		}

		//������ Ŭ���̾�Ʈ ���� ���
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//Ŭ���̾�Ʈ�� ������ ���
		while (1)
		{
			//������ �ޱ�
		RECEIVE_AGAIN:
			retval = recv(client_sock, buf, BUFSIZE, 0);

			if (retval == SOCKET_ERROR)
			{
				//��õ�
				if (WSAGetLastError() == WSAEWOULDBLOCK)
					goto RECEIVE_AGAIN;

				err_display("recv()");
				break;
			}
			else if (retval == 0)
				break;

			//���� ������ ���
			buf[retval] = '\0';
			printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
				ntohs(clientaddr.sin_port), buf);

			//������ ������
		SEND_AGAIN:
			retval = send(client_sock, buf, retval, 0);

			if (retval == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
					goto SEND_AGAIN;

				err_display("send()");

				break;
			}
		}

		//closesocket()
		closesocket(client_sock);

		printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
	}

	//closesocket()
	closesocket(listen_sock);

	//���� ����
	WSACleanup();

	return 0;
}

void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(const char* msg)
{
	PVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	printf("[%s] %s", msg, (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}