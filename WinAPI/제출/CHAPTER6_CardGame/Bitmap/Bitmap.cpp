#include "Bitmap.h"

Bitmap::Bitmap(HWND hWnd, HINSTANCE g_hInst, int bitmapID, int x, int y, int width, int height)
: m_hWnd(hWnd), m_ix(x), m_iy(y), m_iWidth(width), m_iHeight(height)
{
	m_hBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(bitmapID));
	m_hdc = GetDC(m_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);
	m_iId = bitmapID;
	m_fpEvent = nullptr;
	m_strName = nullptr;
}

Bitmap::~Bitmap()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
	ReleaseDC(m_hWnd, m_hdc);
}

LPCWSTR Bitmap::getName()
{
	return m_strName;
}

void Bitmap::setName(LPCWSTR name)
{
	m_strName = name;
}

int Bitmap::getBitmapID()
{
	return m_iId;
}

void Bitmap::setPosition(int x, int y)
{
	m_ix = x;
	m_iy = y;
}

void Bitmap::draw(HDC hdc)
{
	
	PAINTSTRUCT ps;
	HBITMAP oldBitmap;

	oldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	BitBlt(hdc, m_ix, m_iy, m_iWidth, m_iHeight, m_MemDC, 0, 0, SRCCOPY);
	SelectObject(m_MemDC, oldBitmap);

}

