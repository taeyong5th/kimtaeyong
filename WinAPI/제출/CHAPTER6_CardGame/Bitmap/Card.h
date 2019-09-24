#pragma once
#include <Windows.h>
#include "Bitmap.h"

class Card
{
private:
	bool m_bIsOpened; // ī�尡 �������� ���� ����
	int m_iBitmapID; // �׷��� ��Ʈ�� id
	int m_iClosedBitmapID; // ī�尡 ���������� �׷��� ��Ʈ�� id
	int m_ix, m_iy; // ī�尡 �׷��� �»� ��ġ
	int m_iWidth, m_iHeight;
	void (*m_fpEvent)(HWND, Card*); // �̺�Ʈ �߻��� ������ �Լ�

public:
	void open();
	void close();
	bool isOpen();
	int getBitmapID();
	int getX();
	int getY();
	bool isVaildRange(int x, int y); // x, y ��ǥ�� ��Ʈ�� �̹����ȿ� �ִ��� Ȯ��
	void setEventFunction(void (*func)(HWND hwnd, Card* card));
	void runClickEvent(HWND hwnd, int x, int y);
	Card(int bitmapID, int closedBitmapID, int x, int y, int width, int height);
	~Card();
};