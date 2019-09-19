#include <windows.h>
#include "Figure.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut");
Figure *figure; // �׷��� ����
const int moveGap = 5; // Ű ������ �� �̵��� �Ÿ�
//3. Mouse�����͸� �߽����� ����ٴϴ� ���� Rect������ ���� �� �ȿ��� �����
//   �ʰ� ����ٴϴ� ���� ������.
RECT rect; // ���� �׷����� rect ����

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	// figure �ʱ���ġ �� ũ��
	figure = new Figure(hWnd, 100, 100, 50, 50);
	// rect �ʱ�ȭ
	rect.top = 20;
	rect.left = 20;
	rect.bottom = 200;
	rect.right = 400;
	figure->setRect(&rect);

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
	int x, y;

	switch (iMessage)
	{
	//1. left, right, up, down ��ư���� �����ϴ� ���� ������.
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			figure->moveTo(figure->getX() - moveGap, figure->getY());
			break;
		case VK_RIGHT:
			figure->moveTo(figure->getX() + moveGap, figure->getY());
			break;
		case VK_UP:
			figure->moveTo(figure->getX(), figure->getY() - moveGap);
			break;
		case VK_DOWN:
			figure->moveTo(figure->getX(), figure->getY() + moveGap);
			break;
		}
		InvalidateRect(hWnd, &rect, true);
		return 0;
	//2. Mouse�����͸� �߽����� ����ٴϴ� ���� ����� ����.
	case WM_MOUSEMOVE:
		x = LOWORD(lParam);
		y = HIWORD(lParam);		
		figure->moveTo(x, y);
		InvalidateRect(hWnd, &rect, true);
		return 0;
	//4. MessageBox�� �̿��ؼ� ���� �簢��, �簢���� ������ �ٲٴ� ���� ������
	case WM_RBUTTONDOWN:
		if (MessageBox(hWnd, TEXT("���� ����� �����ϰڽ��ϱ�?"), TEXT("���� ����"), MB_YESNO) == IDYES)
		{
			figure->changeShape();
		}
		InvalidateRect(hWnd, &rect, true);
		return 0;
	case WM_PAINT:
		figure->draw();
		return 0;
	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("�����Ͻðڽ��ϱ�?"), TEXT("����"), MB_YESNO) == IDYES)
		{
			PostQuitMessage(0);
		}
		return 0;
	case WM_DESTROY:
		delete figure;
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
