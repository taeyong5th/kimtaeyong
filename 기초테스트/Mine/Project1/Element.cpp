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
	m_MapDraw.DrawPoint(getShape(), m_ix, m_iy);
}

string Element::getShape()
{
	if (m_bFlag) return "＃";
	if (!m_bIsOpen) return "■";

	switch (m_iData)
	{
	case MINE:
		return "★";
	case 0:
		return "  ";// "０";
	case 1:
		return "１";
	case 2:
		return "２";
	case 3:
		return "３";
	case 4:
		return "４";
	case 5:
		return "５";
	case 6:
		return "６";
	case 7:
		return "７";
	case 8:
		return "８";
	default:
		return "■";
	}
}
