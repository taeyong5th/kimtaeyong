#include "GameinfoUI.h"

GameinfoUI::GameinfoUI()
{
	// ��ư ����
	m_btnTurn = new Button(500, 0, 200, 50, L"�� : 0");
	m_btnTeam = new Button(500, 50, 200, 50, L"�� �÷��̾� ����");
}

GameinfoUI::~GameinfoUI()
{
	delete m_btnTurn;
	delete m_btnTeam;
}

void GameinfoUI::draw(HDC hdc, TEAM team, UINT turnCount)
{
	TCHAR text[256];

	wsprintf(text, TEXT("�� : %d"), turnCount);
	m_btnTurn->setText(text);
	m_btnTurn->draw(hdc);
		
	switch (team)
	{
	case TEAM_BLACK:
		m_btnTeam->setText(L"�� �÷��̾� ����");
		break;
	case TEAM_WHITE:
		m_btnTeam->setText(L"�� �÷��̾� ����");
		break;
	}
	m_btnTeam->draw(hdc);
}
