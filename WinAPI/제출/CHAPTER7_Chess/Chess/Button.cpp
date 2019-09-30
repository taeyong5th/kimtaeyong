#include "Button.h"


Button::Button()
{
	m_Rect.left = 0;
	m_Rect.top = 0;
	m_Rect.right = 0;
	m_Rect.bottom = 0;
	m_strText = nullptr;
}

Button::Button(int x, int y, int width, int height, LPCWSTR text)
{
	m_Rect.left = x;
	m_Rect.top = y;
	m_Rect.right = x + width; 
	m_Rect.bottom = y + height;	
	m_strText = new wchar_t[sizeof(wchar_t) * lstrlen(text)];
	wcscpy(m_strText, text);
}

Button::~Button()
{
	delete m_strText;
}

void Button::setPosition(int x, int y, int width, int height)
{
	m_Rect.left = x;
	m_Rect.top = y;
	m_Rect.right = x + width;
	m_Rect.bottom = y + height;
}

void Button::setText(LPCWSTR text)
{
	delete m_strText;
	m_strText = new wchar_t[sizeof(wchar_t) * lstrlen(text)];
	wcscpy(m_strText, text);
}

void Button::draw(HDC hdc)
{
	Rectangle(hdc, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
	SetTextAlign(hdc, TA_CENTER);
	TextOut(hdc, (m_Rect.left + m_Rect.right) / 2, (m_Rect.top + m_Rect.bottom) / 2, m_strText, lstrlen(m_strText));
}

bool Button::isClicked(POINT point)
{
	if (PtInRect(&m_Rect, point))
	{
		return true;
	}
	return false;
}
