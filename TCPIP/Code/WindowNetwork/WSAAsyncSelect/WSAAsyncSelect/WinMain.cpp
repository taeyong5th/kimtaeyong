#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERPORT 9000
#define BUFSIZE 512
#define WM_SOCKET (WM_USER + 1) //��Ʈ��ũ �̺�Ʈ�� ������ ����� ���� ������ �޽���

// ���� ���� ������ ���� ����ü
// �ι��ڿ��� �߰��ϱ� ���� BUFSIZE + 1�̴�.
// ���� ���� ����Ʈ ���� ���� ����Ʈ ���� �����ϱ� ���� ����
// recvdelayed ������ FD_READ �޽����� �޾�����  ���� �Լ��� recv()�Լ��� ȣ������ ���� ��쿡 TRUE�� �����ϰ� �ȴ�.
// next�� ���Ḯ��Ʈ(�ڱ� ���� ����ü)�� �����ϱ� ���� �ʿ��ϴ�. ������ �����ϰ� �޸𸮿� �����ϴ� ��ġ�� ���� �ٸ��� ������
// ���, ������ �������� ���� ũ�⿡ ������ ������ϹǷ�..
struct SOCKETINFO
{
	SOCKET sock;
	char buf[BUFSIZE + 1];
	int recvbytes;
	int sendbytes;
	BOOL recvdelayed;
	SOCKETINFO* next;
};

SOCKETINFO* SocketInfoList;

//���� �޽��� ó��
void ProcessSocketMessage(HWND, UINT, WPARAM, LPARAM);
//WINDOW �޽��� ó��
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//���� ���� �Լ�
BOOL AddSocketInfo(SOCKET sock);
SOCKETINFO* GetSocketInfo(SOCKET sock);
void RemoveSocketInfo(SOCKET sock);

//���� ��� �Լ�
void err_quit(const char* msg);
void err_display(const char* msg);
void err_display(int errcode);

HINSTANCE g_hInst;//�۷ι� �ν��Ͻ��ڵ鰪
LPCTSTR lpszClass = TEXT("WSAAsyncSelect"); //â�̸�

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);	//Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc;	//���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass;	//Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	
	if (hWnd == NULL)
		return 1;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	int retval;

	//���� �ʱ�ȭ
	WSADATA wsa;
	
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	//socket()
	SOCKET listen_sock = socket(AF_INET, SOCK_STREAM, 0);

	if (listen_sock == INVALID_SOCKET)
		err_quit("socket()");

	//bind()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddr.sin_port = htons(SERVERPORT);

	retval = bind(listen_sock, (SOCKADDR*)&serveraddr, sizeof(serveraddr));

	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	//listen()
	retval = listen(listen_sock, SOMAXCONN);

	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	//WSAAsySelect()
	//FD_ACCEPT, FD_CLOSE �̺�Ʈ�� ���
	retval = WSAAsyncSelect(listen_sock, hWnd, WM_SOCKET, FD_ACCEPT | FD_CLOSE);

	if (retval == SOCKET_ERROR)
		err_quit("listen()");

	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}

	//���� ����
	WSACleanup();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
		//����� ���� �޽����� �ް� �Ǹ� ó���ϴ� �κ�
		//�޽��� ó���� ���� ������ ����� ��츦 ����ؼ� ���� �޽����� ó���ϴ� �Լ��� ������ش�.
		//������ �޽����� �״�� ó���ؾ��ϱ⶧���� ���ڸ� �״�� �����ִ� ��Ʈ��ũ �޽��� ó�� �Լ��� ����� �ش�.
	case WM_SOCKET://���� ���� ������ �޽���
		ProcessSocketMessage(hWnd, iMessage, wParam, lParam);
		break;
	case WM_DESTROY:// �����찡 �ı��Ǿ��ٴ� �޼���
		PostQuitMessage(0); //GetMessage�Լ��� WM_QUIT �޽����� ������.
		return 0; //WndProc�� Switch�� break ��� return 0; �� ����.
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam)); // case�� �ִ� �޽����� ������ ������ �޽����� ó���Ѵ�.
}

//���� ���� ������ �޽��� ó��
//���� Ŭ���̾�Ʈ�� ���� ���� �ִ�. Send�� �������� �״�� Recv�ϰ� �ִ� ��ü Ŭ���̾�Ʈ�� �˾ƾ��� �����Ͷ��
//��ü���� ��������Ѵ�. �ش翹������ �׷����� ����. ��ü���� ����Ѵٸ� ��ü�� �ִ� �ڵ带 �߰��غ���.
void ProcessSocketMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//������ ��ſ� ����� ����
	SOCKETINFO *ptr;
	SOCKET client_sock;
	SOCKADDR_IN clientaddr;
	int addrlen, retval;

	//���� �߻� ���� Ȯ��
	if (WSAGETSELECTERROR(lParam))
	{
		err_display(WSAGETSELECTERROR(lParam));
		RemoveSocketInfo(wParam);
		return;
	}

	//�޽��� ó��
	switch (WSAGETSELECTEVENT(lParam))
	{
		//accept() �Լ��� ȣ���ϰ� ���� ���� Ȯ���Ͽ� ������ ó���Ѵ�.
	case FD_ACCEPT:

		addrlen = sizeof(clientaddr);
		client_sock = accept(wParam, (SOCKADDR*)&clientaddr, &addrlen);

		if (client_sock == INVALID_SOCKET)
		{
			err_display("accept()");
			return;
		}

		//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
		printf("\n[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
			inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

		//������ Ŭ���̾�Ʈ ������ ����Ѵ�.
		AddSocketInfo(client_sock);

		//FD_READ, FD_WRITE, FD_CLOSE�� ����Ѵ�.
		retval = WSAAsyncSelect(client_sock, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE);

		if (retval == SOCKET_ERROR)
		{
			err_display("SWAAsyncSelect()");
			RemoveSocketInfo(client_sock);
		}

		break;
	case FD_READ:

		//���� ���� ����ü�� �޴´�.
		ptr = GetSocketInfo(wParam);

		//�̹��� �޾����� ���� ������ ���� ����Ŀ�� �ִٸ� �޾Ҵٴ� ��Ǹ� ����ϰ� �����Ѵ�.
		if(ptr->recvbytes > 0)
		{
			ptr->recvdelayed = TRUE;
			return;
		}

		//�����͹ޱ�
		retval = recv(ptr->sock, ptr->buf, BUFSIZE, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("recv()");
			RemoveSocketInfo(wParam);
			return;
		}

		ptr->recvbytes = retval;

		//���� ������ ���
		ptr->buf[retval] = '\0';
		addrlen = sizeof(clientaddr);
		getpeername(wParam, (SOCKADDR*)&clientaddr, &addrlen);

		//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
		printf("[TCP/%s:%d] %s\n", inet_ntoa(clientaddr.sin_addr),
			ntohs(clientaddr.sin_port), ptr->buf);

		// �̰��� break�� ���ٰ� �̻��Ұ� ���� Write���� ó���ؾ� �ϱ� �����̴�.

	case FD_WRITE:

		ptr = GetSocketInfo(wParam);

		if (ptr->recvbytes <= ptr->sendbytes)
			return;

		//������ ������
		retval = send(ptr->sock, ptr->buf + ptr->sendbytes,
			ptr->recvbytes - ptr->sendbytes, 0);

		if (retval == SOCKET_ERROR)
		{
			err_display("send()");
			RemoveSocketInfo(wParam);
			return;
		}

		ptr->sendbytes += retval;

		//���� �����͸� ��� ���´��� üũ
		//�޾����� ������ ���� ���� �� TRUE�θ� ������ �����͵��� ������
		if (ptr->recvbytes == ptr->sendbytes)
		{
			ptr->recvbytes = ptr->sendbytes = 0;

			if (ptr->recvdelayed)
			{
				ptr->recvdelayed = FALSE;
				PostMessage(hWnd, WM_SOCKET, wParam, FD_READ);
			}
		}

		break;
	case FD_CLOSE:
		RemoveSocketInfo(wParam);
		break;
	}
}

//���� ���� �߰�
BOOL AddSocketInfo(SOCKET sock)
{
	SOCKETINFO* ptr = new SOCKETINFO;

	if (ptr == NULL)
	{
		printf("[����] �޸𸮰� �����մϴ�\n");
		return FALSE;
	}

	ptr->sock = sock;
	ptr->recvbytes = 0;
	ptr->sendbytes = 0;
	ptr->recvdelayed = FALSE;
	ptr->next = SocketInfoList;
	SocketInfoList = ptr;

	return TRUE;
}

//���� ���� ���
SOCKETINFO* GetSocketInfo(SOCKET sock)
{
	SOCKETINFO* ptr = SocketInfoList;

	while (ptr)
	{
		if (ptr->sock == sock)
			return ptr;

		ptr = ptr->next;
	}
	
	return NULL;
}

//���� ���� ����
void RemoveSocketInfo(SOCKET sock)
{
	SOCKADDR_IN clientaddr;
	int addrlen = sizeof(clientaddr);
	getpeername(sock, (SOCKADDR*)&clientaddr, &addrlen);

	//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
	printf("[TCP ����] Ŭ���̾�Ʈ ����: IP �ּ�=%s, ��Ʈ ��ȣ=%d\n",
		inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));

	SOCKETINFO* curr = SocketInfoList;
	SOCKETINFO* prev = NULL;

	while (curr)
	{
		if (curr->sock == sock)
		{
			if (prev)
				prev->next = curr->next;
			else
				SocketInfoList = curr->next;

			closesocket(curr->sock);
		}

		prev = curr;
		curr = curr->next;
	}
}

//���� �Լ� ���� ��� �� ����
void err_quit(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

//���� �Լ� ���� ���
void err_display(const char* msg)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
	printf("[%s] %s", msg, (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

//���� �Լ� ���� ���
void err_display(int errcode)
{
	LPVOID lpMsgBuf;

	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, NULL,
		errcode, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	//ȭ�鿡 ����ؾ� ������ ���� ������� ������ ������� ������ Window�� ǥ�õǴ� �Լ��� �����غ���!!
	printf("[����] %s", (const char*)lpMsgBuf);
	LocalFree(lpMsgBuf);
}
