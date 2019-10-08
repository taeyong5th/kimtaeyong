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


enum DIRECTION
{
	DOWN,
	UP,
	LEFT,
	RIGHT
};

int x = 300;
int y = 300;

HDC g_playerDC, g_backDC;
HBITMAP g_btPlayer, g_btBack;
HBITMAP g_btOldPlayer, g_btOldBack;
BITMAP g_mapInfo;
SIZE g_size;

int frame = 0; // WM_TIMER가 호출될때마다 1씩 증가한다

// 이동 관련 변수
DIRECTION direction = DOWN;
int moveFrame = 0; // moveAnimationPerFrame마다 1씩 증가한다.
const int moveAnimationPerFrame = 15; // 몇 frame마다 이동 애니메이션을 변경할지
const int moveDistance = 10; // 프레임당 이동거리

// 점프 관련 변수
bool bJump = false; // space바를 누르면 true
int jumpFrame = 0; // 점프하는동안 1씩증가한다.  0~9 : 위로 올라감, 10~18 : 아래로 떨어짐
const int jumpDistance = 15; // 프레임당 y축 점프거리

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

		return 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		BitmapManager::GetInstance()->prepare(hdc, L"back.bmp", 0, 0);
		BitmapManager::GetInstance()->prepare(hdc, L"image.bmp", x, y, 2.0f, 2.0f, 0.25f * (moveFrame % 4), 0.25f * direction, 0.25f * (moveFrame % 4) + 0.25f, 0.25f * direction + 0.25f);

		BitmapManager::GetInstance()->draw(hdc, 0, 0, 1000, 800);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		frame++; // timer가 호출될때마다 1씩 증가시킨다.

		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			x -= moveDistance;
			direction = LEFT;
		}	
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			x += moveDistance;
			direction = RIGHT;
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			y -= moveDistance;
			direction = UP;
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			y += moveDistance;
			direction = DOWN;
		}	
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			bJump = true;
		}

		// 이동 프레임 계산
		if (frame % moveAnimationPerFrame == 0)
		{
			moveFrame++;
		}

		// 점프 프레임 및 점프 이동거리 계산
		if (bJump)
		{
			if (jumpFrame < 10)
			{
				y -= jumpDistance;
				jumpFrame++;
			}
			else
			{
				y += jumpDistance;
				jumpFrame++;
			}
			if (jumpFrame > 19)
			{
				jumpFrame = 0;
				bJump = false;
			}
		}

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