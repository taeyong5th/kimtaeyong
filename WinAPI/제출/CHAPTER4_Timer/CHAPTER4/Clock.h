#pragma once
#include <Windows.h>
#include <math.h>

enum FIGURE_SHAPE
{
	FS_RECT,
	FS_ELLIPSE
};

class Clock
{
private:
	float x, y; // ������ �߽� ��ǥ
	float width, height; // ������ ����, ���� ����	
	FIGURE_SHAPE shape;
	const HWND hWnd;
	const RECT* lpRect;
public:
	Clock(HWND hWnd, int x, int y, int width, int height);
	~Clock();

	float getX() { return x; };
	float getY() { return y; };
	void reSize(float width, float height); // ũ�⸦ ����
	void changeShape(); // ������ ����� ����
	void moveTo(float x, float y); // (x, y) ��ǥ�� �̵�
	void draw(); // ������ �׸���.
	void setRect(const RECT *lpRect);
};