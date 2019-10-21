#include "GameObject.h"


void GameObject::setPos(int x, int y)
{
	m_ix = x;
	m_iy = y;
}

void GameObject::setTeam(TEAM team)
{
	m_eTeam = team;
}

TEAM GameObject::getTeam()
{
	return m_eTeam;
}

GameObject::GameObject()
{
	m_ix = m_iy = 0;
	m_iHeight = m_iWidth = 0;
	m_eTeam = TEAM_NEUTRAL;
}

GameObject::~GameObject()
{
}
