#include <windows.h>
#include <ctime>
#include "BitmapManager.h"
#include "resource.h"
#include "CardManager.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");

#define WINDOW_WIDTH 1000 // ������ �ʺ�
#define WINDOW_HEIGHT 700 // ������ ����
#define IDT_GAMETIME 1 // ID_TIMER_GAMETIME ���� �ð� Ÿ�̸�
#define IDT_CARD_OPEN_LOCK 2 // ID_TIMER_CARD_OPEN_LOCK ī�� 2���� Ʋ������ ī�带 ������ ���� Ÿ�̸�

#define BITMAP_COUNT 11 // ����� ��Ʈ�� �̹��� ����
BitmapManager* bitmapManager = BitmapManager::GetInstance(); // ��Ʈ�� �Ŵ���
HBITMAP hBitmap;
Bitmap* bitmap = nullptr;
//const LPCWSTR nameList[CARD_COUNT] = { TEXT("������"), TEXT("ȣ����"), TEXT("����"), TEXT("�ڳ���"), TEXT("��"), TEXT("��"), TEXT("�����"), TEXT("������"), TEXT("������"), TEXT("��") };
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
// ī�� Ŭ���� �߻��� �̺�Ʈ �Լ�
void cardClicked(HWND hWnd, Card* card)
{
	cardManager.choose(card);

	// ī�尡 ��Ī��
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
		// ������ ������ ��Ʈ�� ���� �̸� �ʱ�ȭ
		for (int i = 0; i < BITMAP_COUNT; ++i)
		{
			bitmap = new Bitmap(hWnd, g_hInst, (IDB_CARD1 + i), 10 + 160 * i, 50, 145, 235);
			bitmapManager->add(bitmap);
		}

		// ī�� ���� ����
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				card = new Card(IDB_CARD1 + cardBitmapIDs[i][j], IDB_CARD_BACK, 20 + 160 * j, 100 + 250 * i, 145, 235);
				card->setEventFunction(cardClicked);
				cardManager.add(card);
			}
		}

		// Ÿ�̸� ���
		SetTimer(hWnd, IDT_GAMETIME, 1000, NULL);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_GAMETIME:
			GetLocalTime(&st);
			wsprintf(sTime, TEXT("���� �ð��� %d:%d:%d�Դϴ�."),
				st.wHour, st.wMinute, st.wSecond);
			break;
		case IDT_CARD_OPEN_LOCK:
			KillTimer(hWnd, IDT_CARD_OPEN_LOCK);
			cardManager.update();
			isLocked = false;
			MessageBox(hWnd, TEXT("Ʋ�Ƚ��ϴ�."), TEXT("����"), NULL);
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

		// ��� ī�带 ȭ�鿡 �׸���.
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
