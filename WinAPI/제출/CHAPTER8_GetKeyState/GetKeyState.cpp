#include <windows.h>
#include "BitmapManager.h"
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCWSTR g_szClassName = L"GetKeyState";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}


int x = 300;
int y = 500;

HDC g_playerDC, g_backDC;
HBITMAP g_btPlayer, g_btBack;
HBITMAP g_btOldPlayer, g_btOldBack;
BITMAP g_mapInfo;
SIZE g_size;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		
		SetTimer(hWnd, 1, 10, NULL);
	
		BitmapManager::GetInstance()->add(new Bitmap(hWnd, L"image.bmp"));
		BitmapManager::GetInstance()->add(new Bitmap(hWnd, L"back.bmp"));

		/*hdc = GetDC(hWnd);

		g_playerDC = CreateCompatibleDC(hdc);		
		g_btPlayer = (HBITMAP)LoadImage(NULL, L"image.bmp", IMAGE_BITMAP, 0, 0,
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		(HBITMAP)SelectObject(g_playerDC, g_btPlayer);

		g_backDC = CreateCompatibleDC(hdc);
		g_btBack = (HBITMAP)LoadImage(NULL, L"back.bmp", IMAGE_BITMAP, 0, 0,
			LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
		(HBITMAP)SelectObject(g_backDC, g_btBack);

		GetObject(g_btPlayer, sizeof(g_mapInfo), &g_mapInfo);
		
		g_size.cx = g_mapInfo.bmWidth;
		g_size.cy = g_mapInfo.bmHeight;

		ReleaseDC(hWnd, hdc);*/

		return 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		BitmapManager::GetInstance()->draw(hdc, L"back.bmp", 0, 0);
		//BitmapManager::GetInstance()->draw(hdc, L"image.bmp", x, y, 1.0f, 1.0f);
		BitmapManager::GetInstance()->draw(hdc, L"image.bmp", 0, 0, 1.0f, 1.0f, 0.25f, 0.0f, 0.5f, 0.25f);		

		BitmapManager::GetInstance()->draw(hdc, L"image.bmp", 300, 500, 2.0f, 2.0f, 0.5f, 0.25f, 0.75f, 0.5f);

		//StretchBlt(hdc, 0, 0, 1024, 768, g_backDC, 0, 0, 102, 768, SRCCOPY);
		//TransparentBlt(hdc, x, y, g_size.cx / 4, g_size.cy / 4, g_playerDC, 0, 0, g_size.cx / 4, g_size.cy / 4, RGB(255, 0, 255));
		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		if (GetKeyState(VK_LEFT) & 0x8000)
			x -= 10;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			x += 10;
		if (GetKeyState(VK_UP) & 0x8000)
			y -= 10;
		if (GetKeyState(VK_DOWN) & 0x8000)
			y += 10;

		InvalidateRect(hWnd, NULL, false);

		return 0;

	case WM_DESTROY:
		BitmapManager::GetInstance()->DestroyInstance();
		KillTimer(hWnd, 1);
		PostQuitMessage(0);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
