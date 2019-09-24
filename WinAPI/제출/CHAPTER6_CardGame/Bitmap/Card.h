#pragma once
#include <Windows.h>
#include "Bitmap.h"

class Card
{
private:
	bool m_bIsOpened; // 카드가 보여질지 말지 결정
	int m_iBitmapID; // 그려질 비트맵 id
	int m_iClosedBitmapID; // 카드가 뒤집혔을때 그려질 비트맵 id
	int m_ix, m_iy; // 카드가 그려질 좌상 위치
	int m_iWidth, m_iHeight;
	void (*m_fpEvent)(HWND, Card*); // 이벤트 발생시 수행할 함수

public:
	void open();
	void close();
	bool isOpen();
	int getBitmapID();
	int getX();
	int getY();
	bool isVaildRange(int x, int y); // x, y 좌표가 비트맵 이미지안에 있는지 확인
	void setEventFunction(void (*func)(HWND hwnd, Card* card));
	void runClickEvent(HWND hwnd, int x, int y);
	Card(int bitmapID, int closedBitmapID, int x, int y, int width, int height);
	~Card();
};