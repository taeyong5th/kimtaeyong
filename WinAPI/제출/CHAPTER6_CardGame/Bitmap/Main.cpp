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
#define IDT_GAMETIME 1 // ID_TIMER_GAMETIME 게임 시간 타이머
#define IDT_CARD_OPEN_LOCK 2 // ID_TIMER_CARD_OPEN_LOCK 카드 2장이 틀렸을때 카드를 오픈을 막는 타이머

#define BITMAP_COUNT 11 // 출력할 비트맵 이미지 개수
BitmapManager* bitmapManager = BitmapManager::GetInstance(); // 비트맵 매니저
HBITMAP hBitmap;
Bitmap* bitmap = nullptr;
//const LPCWSTR nameList[CARD_COUNT] = { TEXT("강아지"), TEXT("호랑이"), TEXT("오리"), TEXT("코끼리"), TEXT("소"), TEXT("말"), TEXT("고양이"), TEXT("원숭이"), TEXT("개구리"), TEXT("닭") };
const UINT cardBitmapIDs[2][6] = { {0, 1, 2, 3, 4, 5 }
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


bool isLocked = false;
// 카드 클릭시 발생할 이벤트 함수
void cardClicked(HWND hWnd, Card* card)
{
	cardManager.choose(card);

	// 카드가 매칭되
	if (cardManager.isMatched())
	{
		cardManager.update();
	}
	else if(cardManager.chooseCount() == 2 && !isLocked)
	{
		isLocked = true;
		SetTimer(hWnd, IDT_CARD_OPEN_LOCK, 1000, NULL);
	}
	InvalidateRect(hWnd, NULL, TRUE);
}

SYSTEMTIME st;
static TCHAR sTime[128];

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;	
	int x, y;
	std::list<Card*> cardList;
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
				card = new Card(IDB_CARD1 + cardBitmapIDs[i][j], IDB_CARD_BACK, 20 + 160 * j, 100 + 250 * i, 145, 235);
				card->setEventFunction(cardClicked);
				cardManager.add(card);
			}
		}

		// 타이머 등록
		SetTimer(hWnd, IDT_GAMETIME, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_GAMETIME:
			GetLocalTime(&st);
			wsprintf(sTime, TEXT("지금 시간은 %d:%d:%d입니다."),
				st.wHour, st.wMinute, st.wSecond);
			break;
		case IDT_CARD_OPEN_LOCK:
			KillTimer(hWnd, IDT_CARD_OPEN_LOCK);
			cardManager.update();
			isLocked = false;
			MessageBox(hWnd, TEXT("틀렸습니다."), TEXT("실패"), NULL);
			break;
		}
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		cardManager.runClickEvent(hWnd, x, y);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		TextOut(hdc, WINDOW_WIDTH / 2, 10, sTime, lstrlen(sTime));

		// 모든 카드를 화면에 그린다.
		cardList = cardManager.getCardList();
		for (it = cardList.rbegin(); it != cardList.rend(); ++it)
		{
			card = *it;
			bitmapManager->draw(hdc, card->getBitmapID(), card->getX(), card->getY());
		}

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, IDT_GAMETIME);
		delete bitmapManager;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
