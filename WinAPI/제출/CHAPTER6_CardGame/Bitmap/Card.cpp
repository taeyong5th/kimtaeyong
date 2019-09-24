#include "Card.h"

void Card::open()
{
	m_eState = CARD_OPENED;
}

void Card::close()
{
	m_eState = CARD_CLOSED;
}

bool Card::isOpened()
{
	switch (m_eState)
	{
	case CARD_OPENED:
	case CARD_MATCHED:
		return true;
	case CARD_CLOSED:
		return false;
	default:
		return false;
	}
}

void Card::setState(CARD_STATE state)
{
	m_eState = state;
}

CARD_STATE Card::getState()
{
	return m_eState;
}

int Card::getBitmapID()
{
	if (isOpened())
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
	// Ŭ���� ��ǥ x, y�� �̹��� ���� ���̸� �̺�Ʈ �߻�
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
	m_eState = CARD_CLOSED;
	m_fpEvent = nullptr;
}


Card::~Card()
{
}
