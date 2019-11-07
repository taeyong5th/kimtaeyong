#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int main()
{
	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return 1;
	}

	/*------------------*/
	/*   IPv4 ��ȯ����   */
	/*------------------*/
	//������ IPv4 �ּ����
	const char *ipv4test = "147.46.114.70";
	printf("IPv4 �ּ�(��ȯ ��) = %s\n", ipv4test);

	//inet_addr() �Լ�����
	printf("IPv4 �ּ�(��ȯ ��) = 0x%x\n", inet_addr(ipv4test));

	//inet_ntoa() �Լ�����
	IN_ADDR ipv4num;
	ipv4num.s_addr = inet_addr(ipv4test);
	printf("IPv4 �ּ�(�ٽ� ��ȯ ��) = %s\n", inet_ntoa(ipv4num));

	printf("\n");
	system("pause");

	WSACleanup();

	return 0;
}