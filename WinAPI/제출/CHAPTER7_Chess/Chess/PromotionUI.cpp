#include "PromotionUI.h"

PromotionUI::PromotionUI()
{
	// ¹öÆ° »ý¼º
	m_btnQueen = new Button(50, 220, 80, 50, L"Äý");
	m_btnRook = new Button(150, 220, 80, 50, L"·è");
	m_btnBishop = new Button(250, 220, 80, 50, L"ºñ¼ó");
	m_btnKnight = new Button(350, 220, 80, 50, L"³ªÀÌÆ®");
}

PromotionUI::~PromotionUI()
{
	delete m_btnQueen;
	delete m_btnRook;
	delete m_btnBishop;
	delete m_btnKnight;
}

void PromotionUI::draw(HDC hdc)
{
	m_btnQueen->draw(hdc);
	m_btnRook->draw(hdc);
	m_btnBishop->draw(hdc);
	m_btnKnight->draw(hdc);
}

PROMOTION_BUTTON PromotionUI::click(POINT point)
{
	if (m_btnQueen->isClicked(point))
	{
		return BUTTON_QUEEN;
	}
	else if (m_btnRook->isClicked(point))
	{
		return BUTTON_ROOK;
	}
	else if (m_btnBishop->isClicked(point))
	{
		return BUTTON_BISHOP;
	}
	else if (m_btnKnight->isClicked(point))
	{
		return BUTTON_KNIGHT;
	}
	else
	{
		return BUTTON_NONE;
	}
}
