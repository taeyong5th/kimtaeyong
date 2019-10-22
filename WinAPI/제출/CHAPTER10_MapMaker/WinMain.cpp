#include <windows.h>
#include "resource.h"
#include "GameManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MapMaker");
GameManager g_Game;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;

	//메뉴 리소스를 작성해서 윈도우 클래스에 배치
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	g_Game.initResource(hWnd);
	g_Game.init();
	while (true)
	{
		// 메시지큐에 메시지가 있으면 메시지 처리
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
				break;

			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
		{
			g_Game.start();
		}
	}

	return (int)Message.wParam;
}

BLOCK_TYPE types[3] = {BLOCK_TYPE_A, BLOCK_TYPE_A_HARD, BLOCK_TYPE_WATER};

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memDC;
	PAINTSTRUCT ps;
	HBITMAP hbitmap, oldBitmap;
	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_MENU_NEWGAME:
			g_Game.init();
			break;
		case ID_FILE_LOAD:
			g_Game.load();
			break;
		case ID_FILE_SAVE:
			g_Game.save();
			break;
		}

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

int charToInt(const TCHAR* str)
{
	int n = 0;
	for (int i = 0; str[i] != 0; ++i)
	{
		n = n * 10;
		n += str[i] - '0';
	}
	return n;
}
