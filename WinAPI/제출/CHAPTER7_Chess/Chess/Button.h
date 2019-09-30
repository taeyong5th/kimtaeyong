#pragma once
#include <Windows.h>
#pragma warning(disable: 4996)

class Button
{
private:
	RECT m_Rect;
	LPWSTR m_strText;
public:
	Button();
	Button(int x, int y, int width, int height, LPCWSTR text);
	~Button();
	void setPosition(int x, int y, int width, int height);
	void setText(LPCWSTR text);
	void draw(HDC hdc);
	bool isClicked(POINT point);

};