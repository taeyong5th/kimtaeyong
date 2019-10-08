#include "Bitmap.h"

Bitmap::Bitmap(HWND hWnd, LPCWSTR fileName)
	: m_hWnd(hWnd), m_strFileName(fileName)
{
	m_hBitmap = (HBITMAP)LoadImage(NULL, fileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_hdc = GetDC(m_hWnd);
	m_MemDC = CreateCompatibleDC(m_hdc);
	m_fpEvent = nullptr;
	m_strName = nullptr;

	SelectObject(m_MemDC, m_hBitmap);

	BITMAP BitMap_Info;
	GetObject(m_hBitmap, sizeof(BitMap_Info), &BitMap_Info);

	m_iWidth = BitMap_Info.bmWidth;
	m_iHeight = BitMap_Info.bmHeight;

	ReleaseDC(m_hWnd, m_hdc);
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

int Bitmap::getWidth()
{
	return m_iWidth;
}

int Bitmap::getHeight()
{
	return m_iHeight;
}

LPCWSTR Bitmap::getBitmapFileName()
{
	return m_strFileName;
}

void Bitmap::prepare(HDC memDC, int x, int y, float px, float py, float sx, float sy, float ex, float ey)
{
	PAINTSTRUCT ps;

	px = px > 0.0f ? px : 1.0f;
	py = py > 0.0f ? py : 1.0f;

	//BitBlt(hdc, x, y, m_iWidth, m_iHeight, m_MemDC, 0, 0, SRCCOPY);
	//TransparentBlt(hdc, x, y, m_iWidth * px, m_iHeight * py, m_MemDC, 0, 0, m_iWidth, m_iHeight, RGB(255, 0, 255));
	TransparentBlt(memDC, x, y, m_iWidth * (ex - sx) * px , m_iHeight * (ey - sy) * py , m_MemDC, m_iWidth * sx, m_iHeight * sy, m_iWidth * (ex - sx), m_iHeight * (ey - sy), RGB(255, 0, 255));

	//SelectObject(m_MemDC, oldBitmap);
}

