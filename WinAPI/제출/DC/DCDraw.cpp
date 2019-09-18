#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut"); 

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;


	/*RECT rt = { 100, 100, 400, 300 };
	LPCSTR str = TEXT("So keep your eyes on me now"
		"무엇을 보든 좋아할 거야 닿을 수 없는 Level"
		"나와 대결 원한 널 확신해");*/

	float x, y;
	const float move_x = 200, move_y = 200; // 원의 중심좌표
	const float r = 100; // 원의 반지름 길이
	const int a = 100, b = 50; // 타원의 가로세로 길이

	HBRUSH brush;

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		//SetTextAlign(hdc, TA_CENTER);
		//TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);

		/*for(int i = 0; i < 100; i++)
			SetPixel(hdc, 10 + (i * 3), 10, RGB(255, 0, 0));

		MoveToEx(hdc, 50, 50, NULL);
		LineTo(hdc, 300, 90);
		Rectangle(hdc, 50, 100, 200, 180);
		Ellipse(hdc, 220, 100, 400, 200);*/

		//brush = CreateSolidBrush(RGB(0, 20, 255));
		//SelectObject(hdc, brush);

		Ellipse(hdc, 220, 100, 400, 200);

		// 원
		for (float angle = 0; angle <= (2 * 3.14f); angle += 0.01f)
		{
			x = move_x + r * cosf(angle);
			y = move_y + r * sinf(angle);
			SetPixel(hdc, x, y, RGB(0, 250, 100));
		}

		// 타원
		for (x = -a; x <= a; x += 0.1f)
		{
			y = b * sqrtf(1 - (x * x) / (a * a));
			SetPixel(hdc, x + move_x, y + move_y, RGB(0, 0, 250));
			SetPixel(hdc, x + move_x, -y + move_y, RGB(0, 0, 250));
		}

		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);

		ReleaseDC(hWnd, hdc);
		return 0; 
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
