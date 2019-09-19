#include <windows.h>
#include "Figure.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");
Figure *figure; // 그려질 도형
const int moveGap = 5; // 키 눌렸을 때 이동할 거리
//3. Mouse포인터를 중심으로 따라다니는 원을 Rect영역을 만들어서 그 안에서 벗어나지
//   않고 따라다니는 원을 만들어보자.
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
	figure = new Figure(hWnd, 100, 100, 50, 50);
	// rect 초기화
	rect.top = 20;
	rect.left = 20;
	rect.bottom = 200;
	rect.right = 400;
	figure->setRect(&rect);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int x, y;

	switch (iMessage)
	{
	//1. left, right, up, down 버튼으로 조작하는 원을 만들어보자.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			figure->moveTo(figure->getX() - moveGap, figure->getY());
			break;
		case VK_RIGHT:
			figure->moveTo(figure->getX() + moveGap, figure->getY());
			break;
		case VK_UP:
			figure->moveTo(figure->getX(), figure->getY() - moveGap);
			break;
		case VK_DOWN:
			figure->moveTo(figure->getX(), figure->getY() + moveGap);
			break;
		}
		InvalidateRect(hWnd, &rect, true);
		return 0;
	//2. Mouse포인터를 중심으로 따라다니는 원을 만들어 보자.
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);		
		figure->moveTo(x, y);
		InvalidateRect(hWnd, &rect, true);
		return 0;
	//4. MessageBox를 이용해서 원을 사각형, 사각형을 원으로 바꾸는 것을 만들어보자
	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("도형 모양을 변경하겠습니까?"), TEXT("도형 변경"), MB_YESNO) == IDYES)
		{
			figure->changeShape();
		}
		InvalidateRect(hWnd, &rect, true);
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
