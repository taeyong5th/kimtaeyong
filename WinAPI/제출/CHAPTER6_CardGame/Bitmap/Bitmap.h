#pragma once
#include <Windows.h>

class Bitmap
{
private:	
	HBITMAP m_hBitmap; // 비트맵 정보
	LPCWSTR m_strName;
	HWND m_hWnd;
	HDC m_hdc, m_MemDC;
	int m_iId; // bitmap ID
	int m_ix, m_iy, m_iWidth, m_iHeight; 
	void (*m_fpEvent)(HWND, Bitmap*); // 이벤트 발생시 수행할 함수
public:
	Bitmap(HWND hWnd, HINSTANCE g_hInst, int bitmapID, int x, int y, int width, int height);
	~Bitmap();
	LPCWSTR getName();
	void setName(LPCWSTR name);
	int getBitmapID();
	void setPosition(int x, int y);
	void draw(HDC hdc);
};