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
	// flag�� �����ְų� �̹� ���� �Ǿ����� return
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
	if (m_bFlag) return "��";
	if (!m_bIsOpen) return "��";

	switch (m_iData)
	{
	case MINE:
		return "��";
	case 0:
		return "  ";// "��";
	case 1:
		return "��";
	case 2:
		return "��";
	case 3:
		return "��";
	case 4:
		return "��";
	case 5:
		return "��";
	case 6:
		return "��";
	case 7:
		return "��";
	case 8:
		return "��";
	default:
		return "��";
	}
}
