#include <winsock2.h>

int main()
{
	WSADATA wsa;

	//���� �ʱ�ȭ
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	MessageBox(NULL, "���� �ʱ�ȭ ����", "�˸�", MB_OK);

	//���� ����
	WSACleanup();

	return 0;
}