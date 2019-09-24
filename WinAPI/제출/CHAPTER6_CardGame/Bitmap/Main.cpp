#include <windows.h>
#include <ctime>
#include "BitmapManager.h"
#include "resource.h"
#include "CardManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

#define WINDOW_WIDTH 1000 // 윈도우 너비
#define WINDOW_HEIGHT 700 // 윈도우 높이

#define BITMAP_COUNT 11 // 출력할 비트맵 이미지 개수
BitmapManager* bitmapManager = BitmapManager::GetInstance(); // 비트맵 매니저
HBITMAP hBitmap;
Bitmap* bitmap = nullptr;
//const LPCWSTR nameList[CARD_COUNT] = { TEXT("강아지"), TEXT("호랑이"), TEXT("오리"), TEXT("코끼리"), TEXT("소"), TEXT("말"), TEXT("고양이"), TEXT("원숭이"), TEXT("개구리"), TEXT("닭") };
const UINT cardList[2][6] = { {0, 1, 2, 3, 4, 5 }
							 ,{1, 3, 5, 2, 4, 0 } };

Card* card = nullptr;
CardManager cardManager;

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
void bitmapEvent(HWND hWnd, Card* card)
{
	if (!card->isOpen())
		card->open();
	else
		card->close();

	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	int x, y;
	
	std::list<Card*>::reverse_iterator it;

	switch (iMessage)
	{
	case WM_CREATE:
		srand(time(NULL));
		// 윈도우 생성시 비트맵 정보 미리 초기화
		for (int i = 0; i < BITMAP_COUNT; ++i)
		{
			bitmap = new Bitmap(hWnd, g_hInst, (IDB_CARD1 + i), 10 + 160 * i, 50, 145, 235);
			bitmapManager->add(bitmap);
		}

		// 카드 정보 생성
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				card = new Card(IDB_CARD1 + cardList[i][j], IDB_CARD_BACK, 20 + 160 * j, 100 + 250 * i, 145, 235);
				card->setEventFunction(bitmapEvent);
				cardManager.add(card);
			}
		}
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		cardManager.runClickEvent(hWnd, x, y);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (it = cardManager.m_CardList.rbegin(); it != cardManager.m_CardList.rend(); ++it)
		{
			card = *it;
			bitmapManager->draw(hdc, card->getBitmapID(), card->getX(), card->getY());
		}
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		delete bitmapManager;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
