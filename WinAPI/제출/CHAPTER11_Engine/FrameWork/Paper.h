#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"

enum PAPER_COLOR
{
	PAPER_COLOR_NONE = -1, 
	PAPER_COLOR_GREEN, 
	PAPER_COLOR_RED,	
	PAPER_COLOR_YELLOW,
	PAPER_COLOR_BLUE,
	PAPER_COLOR_COUNT
};


class Paper
{
private:
	JEngine::BitMap* m_pBitmap;
	PAPER_COLOR m_eColor;

public:
	void init(PAPER_COLOR color);
	void draw(int x, int y);
	PAPER_COLOR getColor();
	Paper();
	~Paper();
};