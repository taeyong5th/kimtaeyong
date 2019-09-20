#include <windows.h>
#include "Clock.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("PROJECT4 EXAMPLE");
Clock *clock; // �׷��� ����
const int width = 250; // ���� ũ��
const int height = 250; // ���� ũ��
int moveGap = 5; // Ű ������ �� �̵��� �Ÿ�
RECT rect; // ���� �׷����� rect ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// �ð� �ʱ���ġ �� ũ��
	clock = new Clock(hWnd, 200, 200, width, height);
	// rect �ʱ�ȭ
	rect.top = 20;
	rect.left = 20;
	rect.bottom = 400;
	rect.right = 400;
	clock->setRect(&rect);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, &rect, true);
		return 0;
	case WM_PAINT:
		clock->draw();
		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("����"), MB_YESNO) == IDYES)
		{
			PostQuitMessage(0);
		}
		return 0;
	case WM_DESTROY:
		delete clock;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
