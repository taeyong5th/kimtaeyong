#include "Bitmap.h"

Bitmap::Bitmap(HWND hWnd, HBITMAP bitmap, int x, int y, int width, int height)
: m_hBitmap(bitmap), m_ix(x), m_iy(y), m_iWidth(width), m_iHeight(height)
{
	m_MemDC = CreateCompatibleDC(GetDC(hWnd));
	m_fpEvent = nullptr;
	m_strName = nullptr;
}

Bitmap::~Bitmap()
{
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

LPCWSTR Bitmap::getName()
{
	return m_strName;
}

void Bitmap::setName(LPCWSTR name)
{
	m_strName = name;
}

void Bitmap::draw(HDC hdc)
{
	
	PAINTSTRUCT ps;
	HBITMAP oldBitmap;

	oldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	BitBlt(hdc, m_ix, m_iy, m_iWidth, m_iHeight, m_MemDC, 0, 0, SRCCOPY);
	SelectObject(m_MemDC, oldBitmap);

}

void Bitmap::setEventFunction(void (*func)(HWND hwnd, Bitmap* bitmap))
{
	m_fpEvent = func;
}

void Bitmap::runClickEvent(HWND hWnd, int x, int y)
{
	// 클릭된 좌표 x, y가 이미지 범위 안이면 이벤트 발생
	if (isVaildRange(x, y))
	{
		if(m_fpEvent != nullptr)
			m_fpEvent(hWnd, this);
	}
}

bool Bitmap::isVaildRange(int x, int y)
{
	if (m_ix <= x && x <= (m_ix + m_iWidth) && m_iy <= y && y <= (m_iy + m_iHeight))
	{
		return true;
	}
	return false;
}
