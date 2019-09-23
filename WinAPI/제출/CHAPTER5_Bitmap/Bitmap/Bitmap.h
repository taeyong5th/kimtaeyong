#pragma once
#include <Windows.h>

class Bitmap
{
private:
	HBITMAP m_hBitmap; // 비트맵 정보
	int m_ix, m_iy, m_iWidth, m_iHeight; 
	void (*m_fpEvent)(HWND); // 이벤트 발생시 수행할 함수
public:
	Bitmap(HBITMAP bitmap, int x, int y, int width, int height);
	~Bitmap();
	void Draw(HDC hdc);
	void setEventFunction(void (*func)(HWND hwnd));
	void runClickEvent(int x, int y, HWND hwnd); 
};