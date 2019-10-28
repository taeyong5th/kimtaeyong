#include "Paper.h"
#include "ResoucesManager.h"

void Paper::init(PAPER_COLOR color)
{
	switch (color)
	{
	case PAPER_COLOR_RED:
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperRed.bmp");
		break;
	case PAPER_COLOR_BLUE:
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperBlue.bmp");
		break;
	case PAPER_COLOR_YELLOW:
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperYellow.bmp");
		break;
	case PAPER_COLOR_GREEN:
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperGreen.bmp");
		break;
	default:
		break;
	}
	m_pBitmap->SetAnchor(JEngine::ANCHOR_CENTER);
}

void Paper::draw(int x, int y)
{
	m_pBitmap->Draw(x, y);
}

Paper::Paper()
{
	m_eColor = PAPER_COLOR_RED;
	m_pBitmap = nullptr;
}

Paper::~Paper()
{
}
