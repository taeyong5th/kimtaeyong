#include "GameObject.h"


bool GameObject::isCollision(RECT rect)
{
	RECT result;
	if (IntersectRect(&result, &getRect(), &rect))
	{
		return true;
	}
	return false;
}

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

void GameObject::setState(MOVE_STATE state)
{
	// die 상태에서는 변경 불가
	if (m_eState == MOVE_STATE_DIE) return;
	m_eState = state;
}

MOVE_STATE GameObject::getState()
{
	return m_eState;
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
