#pragma once
#include "GlobalDefine.h"


class GameObject
{
protected:
	TEAM m_eTeam;

	int m_ix, m_iy;
	int m_iWidth, m_iHeight;
	RECT m_MapRect;

public:
	void setPos(int x, int y);
	void setTeam(TEAM team);
	TEAM getTeam();
	GameObject();
	virtual ~GameObject();
};