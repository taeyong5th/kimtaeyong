#include <windows.h>
#include <ctime>
#include "BitmapManager.h"
#include "resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

#define WINDOW_WIDTH 1000 // 윈도우 너비
#define WINDOW_HEIGHT 700 // 윈도우 높이

#define CARD_COUNT 10 // 출력할 비트맵 이미지 개수
BitmapManager* bitmapManager = BitmapManager::GetInstance(); // 비트맵 매니저
HBITMAP hBitmap;
Bitmap* bitmap = nullptr;
const LPCWSTR nameList[CARD_COUNT] = { TEXT("강아지"), TEXT("호랑이"), TEXT("오리"), TEXT("코끼리"), TEXT("소"), TEXT("말"), TEXT("고양이"), TEXT("원숭이"), TEXT("개구리"), TEXT("닭") };

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}


// 비트맵 이미지 클릭시 발생할 이벤트 함수
void bitmapEvent(HWND hWnd, Bitmap* bitmap)
{
	MessageBox(hWnd, bitmap->getName(), TEXT("이름"), MB_OK);
	bitmapManager->remove(bitmap);
	bitmapManager->add(bitmap);
	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	int x, y;
	switch (iMessage)
	{
	case WM_CREATE:
		srand(time(NULL));
		// 윈도우 생성시 비트맵 정보 미리 초기화
		for (int i = 0; i < CARD_COUNT; ++i)
		{
			hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(IDB_BITMAP1 + i));
			bitmap = new Bitmap(hWnd, hBitmap, rand()% (WINDOW_WIDTH - 100), rand() % (WINDOW_HEIGHT - 100), 145, 235);
			bitmap->setName(nameList[i]);
			bitmap->setEventFunction(bitmapEvent);
			bitmapManager->add(bitmap);
		}
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		bitmapManager->runClickEvent(hWnd, x, y);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		bitmapManager->draw(hdc);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		delete bitmapManager;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
