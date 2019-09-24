#include "Card.h"

void Card::open()
{
	m_bIsOpened = true;
}

void Card::close()
{
	m_bIsOpened = false;
}

bool Card::isOpen()
{
	return m_bIsOpened;
}

int Card::getBitmapID()
{
	if (isOpen())
	{
		return m_iBitmapID;
	}
	else
	{
		return m_iClosedBitmapID;
	}
}

int Card::getX()
{
	return m_ix;
}

int Card::getY()
{
	return m_iy;
}

bool Card::isVaildRange(int x, int y)
{
	if (m_ix <= x && x <= (m_ix + m_iWidth) && m_iy <= y && y <= (m_iy + m_iHeight))
	{
		return true;
	}
	return false;
}

void Card::setEventFunction(void(*func)(HWND hwnd, Card* card))
{
	m_fpEvent = func;
}

void Card::runClickEvent(HWND hwnd, int x, int y)
{
	// 클릭된 좌표 x, y가 이미지 범위 안이면 이벤트 발생
	if (isVaildRange(x, y))
	{
		if (m_fpEvent != nullptr)
			m_fpEvent(hwnd, this);
	}
}

Card::Card(int bitmapID, int closedBitmapID, int x, int y, int width, int height) :
	m_iWidth(width), m_iHeight(height)
{
	m_iBitmapID = bitmapID;
	m_iClosedBitmapID = closedBitmapID;
	m_ix = x;
	m_iy = y;
	m_bIsOpened = false;
	m_fpEvent = nullptr;
}


Card::~Card()
{
}
