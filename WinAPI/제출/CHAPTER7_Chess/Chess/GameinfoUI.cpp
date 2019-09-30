#include "GameinfoUI.h"

GameinfoUI::GameinfoUI()
{
	// 버튼 생성
	m_btnTurn = new Button(500, 0, 200, 50, L"턴 : 0");
	m_btnTeam = new Button(500, 50, 200, 50, L"흑 플레이어 차례");
}

GameinfoUI::~GameinfoUI()
{
	delete m_btnTurn;
	delete m_btnTeam;
}

void GameinfoUI::draw(HDC hdc, TEAM team, UINT turnCount)
{
	TCHAR text[256];

	wsprintf(text, TEXT("턴 : %d"), turnCount);
	m_btnTurn->setText(text);
	m_btnTurn->draw(hdc);
		
	switch (team)
	{
	case TEAM_BLACK:
		m_btnTeam->setText(L"흑 플레이어 차례");
		break;
	case TEAM_WHITE:
		m_btnTeam->setText(L"백 플레이어 차례");
		break;
	}
	m_btnTeam->draw(hdc);
}
