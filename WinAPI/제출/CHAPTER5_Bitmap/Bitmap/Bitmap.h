#pragma once
#include <Windows.h>

class Bitmap
{
private:	
	HBITMAP m_hBitmap; // ��Ʈ�� ����
	LPCWSTR m_strName;
	HDC m_MemDC;
	int m_ix, m_iy, m_iWidth, m_iHeight; 
	void (*m_fpEvent)(HWND, Bitmap*); // �̺�Ʈ �߻��� ������ �Լ�
public:
	Bitmap(HWND hWnd, HBITMAP bitmap, int x, int y, int width, int height);
	~Bitmap();
	LPCWSTR getName();
	void setName(LPCWSTR name);
	void draw(HDC hdc);
	void setEventFunction(void (*func)(HWND hwnd, Bitmap *bitmap));
	void runClickEvent(HWND hwnd, int x, int y);
	bool isVaildRange(int x, int y); // x, y ��ǥ�� ��Ʈ�� �̹����ȿ� �ִ��� Ȯ��
};