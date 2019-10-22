#pragma once
#include "GlobalDefine.h"


class GameObject
{
protected:
	TEAM m_eTeam;
	MOVE_STATE m_eState;

	int m_ix, m_iy;
	int m_iWidth, m_iHeight;
	RECT m_MapRect;

	virtual LPCWSTR getShape() = 0;

public:
	bool isCollision(RECT rect); // rect�� �浹����
	virtual RECT getRect() = 0; // �浹 üũ�� rect ��ȯ
	void setPos(int x, int y);
	void setTeam(TEAM team);
	TEAM getTeam();
	void setState(MOVE_STATE state);
	MOVE_STATE getState();
	virtual void init(int x, int y, RECT mapRect) = 0; // x, y ��ġ�� �ʱ�ȭ�Ѵ�.
	virtual void draw() = 0; // �޸� DC�� �׸���
	GameObject();
	virtual ~GameObject();
};