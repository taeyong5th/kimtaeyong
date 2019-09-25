#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM); 
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TransparentBlt");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
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
			 
	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768, 
		NULL, (HMENU)NULL, hInstance, NULL); 

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) 										
	{
		TranslateMessage(&Message); 
		DispatchMessage(&Message); 
	}
	return (int)Message.wParam;
}

enum CHARACTER_SIDE
{
	FRONT, BACK, LEFT, RIGHT
};

#define TIMER_ID1 1

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	int bx, by;
	BITMAP bit;
	static int px = 300, py = 200; // 캐릭터 위치 좌표 position x, position y
	static CHARACTER_SIDE side = FRONT; // 캐릭터가 보고 있는 방향
	static int frame = 0; // timer가 호출될때마다 다음 이미지프레임
	RECT rt = { 10, 10, 200,200 };

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, TIMER_ID1, 300, nullptr);
		return 0;
		// 방향키가 입력되면 캐릭터가 보는 방향를 바꾼다.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			py -= 10;
			side = BACK;
			break;
		case VK_DOWN:
			py += 10;
			side = FRONT;
			break;
		case VK_LEFT:
			px -= 10;
			side = LEFT;
			break;
		case VK_RIGHT:
			px += 10;
			side = RIGHT;
			break;
		}
		InvalidateRect(hWnd, nullptr, true);
		return 0;
	case WM_TIMER:
		frame = (frame + 1) % 4;
		InvalidateRect(hWnd, nullptr, true);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc); 
								  
		hImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;
		
		DrawText(hdc, TEXT("방향키를 눌러 이동"), 18, &rt, DT_LEFT);

		//원본 그대로
		//화면의 (50, 50) 위치에 원본 크기로 원본의 (0, 0) 위치부터 추출하여 그린다
		//BitBlt(hdc, 50, 50, bx, by, hMemDC, 0, 0, SRCCOPY);

		//투명처리
		//RGB(255, 0, 255)(핑크색)을 투명하게 만들고 그린다
		//TransparentBlt(hdc, 350, 50, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));

		//투명처리와 부분그리기
		//이번에는 왼쪽을 보고 있고 한발을 내딛은 캐릭터를 그린다
		TransparentBlt(hdc, px, py, bx / 4, by / 4,
			hMemDC, (bx / 4) * frame, (by / 4) * side, bx / 4, by / 4, RGB(255, 0, 255));

		SelectObject(hMemDC, hOldBitmap); 
		DeleteObject(hImage); 
		DeleteDC(hMemDC); 
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, TIMER_ID1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}