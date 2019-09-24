#pragma once
#include <Windows.h>

class Bitmap
{
private:	
	HBITMAP m_hBitmap; // 비트맵 정보
	LPCWSTR m_strName;
	HDC m_MemDC;
	int m_ix, m_iy, m_iWidth, m_iHeight; 
	void (*m_fpEvent)(HWND, Bitmap*); // 이벤트 발생시 수행할 함수
public:
	Bitmap(HWND hWnd, HBITMAP bitmap, int x, int y, int width, int height);
	~Bitmap();
	LPCWSTR getName();
	void setName(LPCWSTR name);
	void draw(HDC hdc);
	void setEventFunction(void (*func)(HWND hwnd, Bitmap *bitmap));
	void runClickEvent(HWND hwnd, int x, int y);
	bool isVaildRange(int x, int y); // x, y 좌표가 비트맵 이미지안에 있는지 확인
};