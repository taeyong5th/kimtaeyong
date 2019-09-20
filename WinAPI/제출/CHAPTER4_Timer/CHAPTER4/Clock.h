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
	float x, y; // 도형의 중심 좌표
	float width, height; // 도형의 가로, 세로 길이	
	FIGURE_SHAPE shape;
	const HWND hWnd;
	const RECT* lpRect;
public:
	Clock(HWND hWnd, int x, int y, int width, int height);
	~Clock();

	float getX() { return x; };
	float getY() { return y; };
	void reSize(float width, float height); // 크기를 변경
	void changeShape(); // 도형의 모양을 변경
	void moveTo(float x, float y); // (x, y) 좌표로 이동
	void draw(); // 도형을 그린다.
	void setRect(const RECT *lpRect);
};