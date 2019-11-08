#include <windows.h>
#include <fstream>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BITMAP");


BITMAPFILEHEADER bitmapFileHeader;
BITMAPINFOHEADER bitmapInfoHeader;
RGBTRIPLE **rbg;

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
	WndClass.lpszMenuName = nullptr;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);


	while (true)
	{
		while (GetMessage(&Message, NULL, 0, 0))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	std::ifstream of("img.bmp", std::ios::in | std::ios::binary);
	char buf[1000];
	switch (iMessage)
	{
	case WM_CREATE:
		memset(&bitmapFileHeader, 0, sizeof(BITMAPFILEHEADER));
		memset(&bitmapInfoHeader, 0, sizeof(BITMAPINFOHEADER));
		if (!of.is_open())
		{
			return 0;
		}

		// BITMAP HEADER READ
		of.read(buf, sizeof(BITMAPFILEHEADER));
		memcpy(&bitmapFileHeader, buf, sizeof(BITMAPFILEHEADER));

		// BITMAP INFO HEADER READ
		of.read(buf, sizeof(BITMAPINFOHEADER));
		memcpy(&bitmapInfoHeader, buf, sizeof(BITMAPINFOHEADER));

		// 픽셀정보 저장할 메모리 할당
		rbg = new RGBTRIPLE*[bitmapInfoHeader.biHeight];
		for (int i = 0; i < bitmapInfoHeader.biHeight; ++i)
		{
			rbg[i] = new RGBTRIPLE[bitmapInfoHeader.biWidth];
		}

		// BITMAP PIXEL READ
		// pixel 정보가 시작되는 오프셋으로 이동 후 배열에 읽음
		of.seekg(bitmapFileHeader.bfOffBits);
		for (int i = bitmapInfoHeader.biHeight - 1; i >= 0; --i)
		{
			for (int j = 0; j < bitmapInfoHeader.biWidth; ++j)
			{
				of.read(buf, sizeof(RGBTRIPLE));
				memcpy(&rbg[i][j], buf, sizeof(RGBTRIPLE));
				if (rbg[i][j].rgbtGreen == 0 && rbg[i][j].rgbtBlue == 0 && rbg[i][j].rgbtRed == 0)
				{
					rbg[i][j].rgbtRed = 255;
					rbg[i][j].rgbtGreen = 255;
					rbg[i][j].rgbtBlue = 80;
				}
				if (rbg[i][j].rgbtGreen == 255 && rbg[i][j].rgbtBlue == 255 && rbg[i][j].rgbtRed == 255)
				{
					rbg[i][j].rgbtRed -= i;
					rbg[i][j].rgbtGreen -= i;
				}
			}
		}

		of.close();
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		for (int i = 0; i < bitmapInfoHeader.biHeight; ++i)
		{
			for (int j = 0; j < bitmapInfoHeader.biWidth; ++j)
			{
				SetPixel(hdc, j, i, RGB(rbg[i][j].rgbtRed, rbg[i][j].rgbtGreen, rbg[i][j].rgbtBlue));
			}
		}
		
		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
