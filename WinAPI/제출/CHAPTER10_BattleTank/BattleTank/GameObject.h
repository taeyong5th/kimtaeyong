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
	bool isCollision(RECT rect); // rect와 충돌는지
	virtual RECT getRect() = 0; // 충돌 체크용 rect 반환
	void setPos(int x, int y);
	void setTeam(TEAM team);
	TEAM getTeam();
	void setState(MOVE_STATE state);
	MOVE_STATE getState();
	virtual void init(int x, int y, RECT mapRect) = 0; // x, y 위치로 초기화한다.
	virtual void draw() = 0; // 메모리 DC에 그린다
	GameObject();
	virtual ~GameObject();
};