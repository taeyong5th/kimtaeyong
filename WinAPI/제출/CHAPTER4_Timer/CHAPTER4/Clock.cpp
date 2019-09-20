#include "Clock.h"

Clock::Clock(HWND hWnd, int x, int y, int width, int height) :
	hWnd(hWnd), x(x), y(y), width(width), height(height)
{
	shape = FS_ELLIPSE;
	lpRect = nullptr;	
}

Clock::~Clock()
{
}

void Clock::reSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

void Clock::changeShape()
{
	switch (shape)
	{
	case FS_RECT:
		this->shape = FS_ELLIPSE;
		break;
	case FS_ELLIPSE:
		this->shape = FS_RECT;
		break;
	default:
		break;
	}
}

void Clock::moveTo(float x, float y)
{
	if (lpRect == nullptr)
	{
		this->x = x;
		this->y = y;
		return;
	}
	float left = x - width / 2;
	float top = y - height / 2;
	float right = x + width / 2;
	float bottom = y + height / 2;
	this->x = x;
	this->y = y;
	/*if (lpRect->top < top && lpRect->bottom > bottom && lpRect->left < left && lpRect->right > right)
	{
		this->x = x;
		this->y = y;
	}*//*
	if (lpRect->right > right)
	{
		this->x = x;
	}
	else
	{
		this->x = lpRect->right - width / 2;
	}*/

}

void Clock::draw()
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	hdc = BeginPaint(hWnd, &ps);

	if (lpRect != nullptr)
	{
		Rectangle(hdc, lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
	}

	switch (shape)
	{
	case FS_ELLIPSE:
		Ellipse(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		break;
	case FS_RECT:
		Rectangle(hdc, x - width / 2, y - height / 2, x + width / 2, y + height / 2);
		break;
	}

	SYSTEMTIME st;
	GetLocalTime(&st);

	float hourAngle = -((2 * 3.14) / 12 * st.wHour) + (3.14) / 2;
	float minAngle = -((2 * 3.14) / 60 * st.wMinute) + (3.14) / 2;
	float secAngle = -((2 * 3.14) / 60 * st.wSecond) + (3.14) / 2;
	
	// 상단 텍스트 출력
	static TCHAR sTime[128];
	wsprintf(sTime, TEXT("지금 시간은 %d:  %d : %d입니다."),
		st.wHour, st.wMinute, st.wSecond);
	TextOut(hdc, 100, 40, sTime, lstrlen(sTime));

	// 시, 분, 초 바늘 그리기
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + (width / 2 - 10) * cosf(secAngle), y - (height / 2 - 10) * sin(secAngle));
	
	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + (width / 3) * cosf(minAngle), y - (height / 3) * sin(minAngle));

	MoveToEx(hdc, x, y, NULL);
	LineTo(hdc, x + (width / 4) * cosf(hourAngle), y - (height / 4) * sin(hourAngle));

	// 시계 숫자 출력하기
	for (int i = 1; i < 13; i++)
	{
		float angle = -((2 * 3.14) / 12 * i) + (3.14) / 2;
		TCHAR number[3];
		wsprintf(number, TEXT("%d"), i);
		TextOut(hdc, x + (width / 2) * cosf(angle), y - (height / 2) * sin(angle), number, lstrlen(number));
	}

	// 눈금 그리기
	for (int i = 0; i < 60; i++)
	{
		float angle = (2 * 3.14) / 60 * i;
		int s_x, s_y, e_x, e_y;

		s_x = x + (width / 2) * cosf(angle);
		s_y = y + (height / 2) * sinf(angle);
		e_x = x + (width / 2 - 5) * cosf(angle);
		e_y = y + (height / 2 - 5) * sinf(angle);

		MoveToEx(hdc, s_x, s_y, NULL);
		LineTo(hdc, e_x, e_y);

	}

	EndPaint(hWnd, &ps);
}

void Clock::setRect(const RECT* lpRect)
{
	this->lpRect = lpRect;
}
