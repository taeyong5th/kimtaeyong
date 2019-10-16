#include "Element.h"

Element::Element(int x, int y)
{
	m_ix = x;
	m_iy = y;
	m_iData = 0;
	m_bIsOpen = false;
	m_bFlag = false;
}

Element::~Element()
{
}

int Element::getData()
{
	return m_iData;
}

void Element::setData(int data)
{
	if (data < MINE || data > 8) return;
	m_iData = data;
}

bool Element::setFlag()
{
	if (!m_bIsOpen) 
		m_bFlag = !m_bFlag;

	return m_bFlag;
}

bool Element::isFlag()
{
	return m_bFlag;
}

bool Element::isOpen()
{
	return m_bIsOpen;
}

void Element::open()
{
	// flag가 꽂혀있거나 이미 오픈 되었으면 return
	if (m_bFlag || m_bIsOpen) return;

	m_bIsOpen = true;
	draw();
}

void Element::draw()
{
	//m_MapDraw.DrawPoint(getShape(), m_ix, m_iy);
	int width = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK)->getWidth();
	int height = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK)->getHeight();
	BitmapManager::GetInstance()->prepare(getShape(), m_ix * width, m_iy * height);
}

LPCWSTR Element::getShape()
{
	if (m_bFlag) return IMG_FLAG;
	if (!m_bIsOpen) return IMG_BLOCK;

	switch (m_iData)
	{
	case MINE:
		return IMG_MINE;
	case 0:
		return IMG_BLOCK_0;
	case 1:
		return IMG_BLOCK_1;
	case 2:
		return IMG_BLOCK_2;
	case 3:
		return IMG_BLOCK_3;
	case 4:
		return IMG_BLOCK_4;
	case 5:
		return IMG_BLOCK_5;
	case 6:
		return IMG_BLOCK_6;
	case 7:
		return IMG_BLOCK_7;
	case 8:
		return IMG_BLOCK_8;
	default:
		return IMG_BLOCK;
	}
}
