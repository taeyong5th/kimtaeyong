#include "GameinfoUI.h"

GameinfoUI::GameinfoUI()
{
	// ��ư ����
	m_btnTurn = new Button(500, 0, 200, 50, L"�� : 0");
	m_btnTeam = new Button(500, 50, 200, 50, L"�� �÷��̾� ����");
	m_btnReset = new Button(500, 100, 200, 50, L"RESET");
}

GameinfoUI::~GameinfoUI()
{
	delete m_btnTurn;
	delete m_btnTeam;
	delete m_btnReset;
}

void GameinfoUI::update(TEAM team, UINT turnCount)
{

	TCHAR text[256];
	wsprintf(text, TEXT("�� : %d"), turnCount);
	m_btnTurn->setText(text);

	switch (team)
	{
	case TEAM_BLACK:
		m_btnTeam->setText(L"�� �÷��̾� ����");
		break;
	case TEAM_WHITE:
		m_btnTeam->setText(L"�� �÷��̾� ����");
		break;
	}
}

void GameinfoUI::draw(HDC hdc)
{
	m_btnTurn->draw(hdc);
	m_btnTeam->draw(hdc);
	m_btnReset->draw(hdc);
}

GAMEINFO_BUTTON GameinfoUI::click(POINT point)
{
	if (m_btnReset->isClicked(point))
	{
		return GAMEINFO_BUTTON_RESET;
	}
	else
	{
		return GAMEINFO_BUTTON_NONE;
	}
}
