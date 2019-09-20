#include <windows.h>
#include "Figure.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("PROJECT4 EXAMPLE");
Figure *figure; // 그려질 도형
const int width = 50; // 도형 크기
const int height = 50; // 도형 크기
int moveGap = 5; // 키 눌렸을 때 이동할 거리
RECT rect; // 원이 그려지리 rect 범위

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

	// figure 초기위치 및 크기
	figure = new Figure(hWnd, 300, 100, width, height);
	// rect 초기화
	rect.top = 20;
	rect.left = 20;
	rect.bottom = 200;
	rect.right = 600;
	figure->setRect(&rect);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


VOID CALLBACK moveFigure(HWND hWnd, UINT iMessage, UINT_PTR idEvent, DWORD dwTime)
{

	if (rect.right > figure->getX() + width / 2 && moveGap > 0)
	{
		moveGap = 5;
	}
	else if (rect.left > figure->getX() - width / 2 && moveGap < 0)
	{
		moveGap = 5;
	}
	else
	{
		moveGap = -5;
	}

	figure->moveTo(figure->getX() + moveGap, figure->getY());
	
	InvalidateRect(hWnd, nullptr, true);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 10, moveFigure);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;	
	case WM_PAINT:
		figure->draw();
		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("종료하시겠습니까?"), TEXT("종료"), MB_YESNO) == IDYES)
		{
			PostQuitMessage(0);
		}
		return 0;
	case WM_DESTROY:
		delete figure;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
