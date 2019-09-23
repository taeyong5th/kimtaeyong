#include "resource.h"
#include <windows.h>
#include "Bitmap.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

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
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

void showMessageBox(HWND hWnd)
{
	MessageBox(hWnd, TEXT("º“"), TEXT("¿Ã∏ß"), MB_OK);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP myBitmap, myBitmap2;
	myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP3));
	myBitmap2 = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP5));
	Bitmap bmp(myBitmap, 100, 100, 145, 235);
	Bitmap bmp2(myBitmap2, 300, 100, 345, 235);

	bmp2.setEventFunction(showMessageBox);

	int x, y;
	switch (iMessage)
	{
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bmp2.runClickEvent(x, y, hWnd);


		return 0;
	case WM_PAINT:	
		hdc = BeginPaint(hWnd, &ps);
		bmp2.Draw(hdc); 
		bmp.Draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
