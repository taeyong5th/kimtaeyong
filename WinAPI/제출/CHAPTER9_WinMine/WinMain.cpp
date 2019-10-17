#include <windows.h>
#include "resource.h"
#include "GameManager.h"

INT_PTR CALLBACK SettingsDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MineSweeper");
GameManager g_Game;

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	g_Game.initResource(hWnd);
	g_Game.init();
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
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_MENU_NEWGAME:
			g_Game.init();
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

int charToInt(const TCHAR* str)
{
	int n = 0;
	for (int i = 0; str[i] != 0; ++i)
	{
		n = n * 10;
		n += str[i] - '0';
	}
	return n;
}

INT_PTR CALLBACK SettingsDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	HWND hEditRow, hEditCol, hEditMineCount;
	int row, col, mineCount;

	hEditRow = GetDlgItem(hDlg, IDC_EDIT1);
	hEditCol = GetDlgItem(hDlg, IDC_EDIT2);
	hEditMineCount = GetDlgItem(hDlg, IDC_EDIT3);
	TCHAR str[128];
	switch (iMessage)
	{
		case WM_INITDIALOG:
			hRadio = GetDlgItem(hDlg, IDC_RADIO1);
			SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);
			return TRUE;

		case WM_COMMAND:			
			switch (LOWORD(wParam))
			{
				case IDC_EDIT1:
					switch (HIWORD(wParam)) 
					{
					case EN_CHANGE:
						GetWindowText(hEditRow, str, 128);
						row = charToInt(str);
						if (row > MAP_WIDTH_MAX)
						{
							row = 30;
							str[0] = '3';
							str[1] = '0';
							str[2] = '\0';
						}
						//SetWindowText(hEditRow, str);
						break;
					}
					return TRUE;
				case IDC_RADIO1:
				case IDC_RADIO2:
				case IDC_RADIO3:
					SendMessage(hEditRow, EM_SETREADONLY, true, 0);
					SendMessage(hEditCol, EM_SETREADONLY, true, 0);
					SendMessage(hEditMineCount, EM_SETREADONLY, true, 0);
					return TRUE;
				case IDC_RADIO4:
					SendMessage(hEditRow, EM_SETREADONLY, false, 0);
					SendMessage(hEditCol, EM_SETREADONLY, false, 0);
					SendMessage(hEditMineCount, EM_SETREADONLY, false, 0);
					return TRUE;
				case IDOK:
					
					if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
					{
						g_Game.init(GAME_LEVEL_EASY);
					}
					else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
					{
						g_Game.init(GAME_LEVEL_NORMAL);
					}
					else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
					{
						g_Game.init(GAME_LEVEL_HARD);
					}
					else if (IsDlgButtonChecked(hDlg, IDC_RADIO4) == BST_CHECKED)
					{
						GetWindowText(hEditRow, str, 128);
						row = charToInt(str);
						GetWindowText(hEditCol, str, 128);
						col = charToInt(str);
						GetWindowText(hEditMineCount, str, 128);
						mineCount = charToInt(str);
						g_Game.init(GAME_LEVEL_USER, row, col, mineCount);
					}

					EndDialog(hDlg, 0);

					return TRUE;

				case IDCANCEL:
					EndDialog(hDlg, 0);
					return TRUE;
			}

			break;
	}

	return FALSE;
}
