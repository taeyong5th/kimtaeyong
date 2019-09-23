#include "Bitmap.h"

Bitmap::Bitmap(HBITMAP bitmap, int x, int y, int width, int height)
: m_hBitmap(bitmap), m_ix(x), m_iy(y), m_iWidth(width), m_iHeight(height)
{
	m_fpEvent = nullptr;
}

Bitmap::~Bitmap()
{
}

void Bitmap::Draw(HDC hdc)
{
	HDC MemDC;
	PAINTSTRUCT ps;
	HBITMAP oldBitmap;


	MemDC = CreateCompatibleDC(hdc);	
	oldBitmap = (HBITMAP)SelectObject(MemDC, m_hBitmap);
	BitBlt(hdc, m_ix, m_iy, m_iWidth, m_iHeight, MemDC, 0, 0, SRCCOPY);
	SelectObject(MemDC, oldBitmap);

	DeleteObject(m_hBitmap);
	DeleteDC(MemDC);

}

void Bitmap::setEventFunction(void (*func)(HWND hwnd))
{
	m_fpEvent = func;
}

void Bitmap::runClickEvent(int x, int y, HWND hWnd)
{
	// Ŭ���� ��ǥ x, y�� �̹��� ���� ���̸� �̺�Ʈ �߻�
	if (m_ix <= x && x <= (m_ix + m_iWidth) && m_iy <= y && y <= (m_iy + m_iHeight))
	{
		if(m_fpEvent != nullptr)
			m_fpEvent(hWnd);
	}
}
