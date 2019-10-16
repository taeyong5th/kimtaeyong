#include <windows.h>
#include "GameManager.h"
#include "resource.h"

BOOL CALLBACK SettingsDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MineSweeper");
GameManager g_Game;
int g_iWindowWidth = 700;
int g_iWindowHeight = 700;

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, g_iWindowWidth, g_iWindowHeight, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	g_Game.initResource(hWnd);

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case 0:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SettingsDlgProc);
			return 0;
		case ID_MENU_NEWGAME:
			g_Game.init(15, 15);
			break;
		case ID_MENU_SETTINGS:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, SettingsDlgProc);
			break;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}


HWND level1, level2, level3;
enum
{
	ID_SETTING_L1,
	ID_SETTING_L2,
	ID_SETTING_L3
};
BOOL CALLBACK SettingsDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	switch (iMessage)
	{
	case WM_INITDIALOG:

		CreateWindow(TEXT("button"), TEXT("난이도 설정"), WS_CHILD | WS_VISIBLE |
			BS_GROUPBOX, 5, 5, 200, 180, hDlg, (HMENU)0, g_hInst, NULL);

		level1 = CreateWindow(TEXT("button"), TEXT("초급"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON | WS_GROUP, 20, 30, 110, 20, hDlg, (HMENU)ID_SETTING_L1, g_hInst, NULL);
		level2 = CreateWindow(TEXT("button"), TEXT("중급"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 20, 70, 110, 20, hDlg, (HMENU)ID_SETTING_L2, g_hInst, NULL);
		level3 = CreateWindow(TEXT("button"), TEXT("고급"), WS_CHILD | WS_VISIBLE |
			BS_AUTORADIOBUTTON, 20, 110, 110, 20, hDlg, (HMENU)ID_SETTING_L3, g_hInst, NULL);

		CheckRadioButton(hDlg, ID_SETTING_L1, ID_SETTING_L3, ID_SETTING_L1);

		return TRUE;
	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			return TRUE;
		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
	}

	return FALSE;
}