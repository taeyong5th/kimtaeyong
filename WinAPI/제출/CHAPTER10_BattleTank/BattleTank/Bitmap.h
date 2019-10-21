#pragma once
#include <Windows.h>

class Bitmap
{
private:	
	HBITMAP m_hBitmap; // ∫Ò∆Æ∏  ¡§∫∏
	LPCWSTR m_strName;
	HWND m_hWnd;
	HDC m_hdc, m_MemDC;
	LPCWSTR m_strFileName; 
	int m_iWidth, m_iHeight;
public:
	Bitmap(HWND hWnd, LPCWSTR fileName);
	~Bitmap();
	LPCWSTR getName();
	void setName(LPCWSTR name);
	int getWidth();
	int getHeight();
	LPCWSTR getBitmapFileName();
	void draw(HDC memDC, int x, int y, float px = 1.0f, float py = 1.0f, float sx = 0.0f, float sy = 0.0f, float ex = 1.0f, float ey = 1.0f);
};