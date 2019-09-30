#pragma once
#include <Windows.h>
#include "Button.h"

enum PROMOTION_BUTTON
{
	BUTTON_NONE,
	BUTTON_QUEEN,
	BUTTON_ROOK,
	BUTTON_BISHOP,
	BUTTON_KNIGHT
};

class PromotionUI
{
private:
	Button* m_btnQueen, * m_btnRook, * m_btnBishop, * m_btnKnight;

public:
	PromotionUI();
	~PromotionUI();
	void draw(HDC hdc);
	PROMOTION_BUTTON click(POINT point);
};