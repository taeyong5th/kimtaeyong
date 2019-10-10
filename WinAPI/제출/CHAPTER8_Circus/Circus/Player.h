#pragma once
#include "GameDefine.h"

enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_MOVE,
	PLAYER_STATE_JUMP,
	PLAYER_STATE_DIE,
	PLAYER_STATE_WIN
};

class Player
{
private:
	int m_ix, m_iy; // 캐릭터가 그려질 위치(좌상단이 아닌 중심위치)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // 원본 이미지의 몇 배크기로 그릴지	
	PLAYER_STATE m_eState;

	LPCWSTR m_aMoveAnimation[3];
	LPCWSTR m_aWinAnimation[2];

	RECT m_Rect; // 충돌 범위
	
	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fMoveAnimTick; // 움직일때 애니메이션을 몇초마다 바뀌게 할지
	float m_fJumpTick; // 점프 동작
public:
	RECT getRect();
	void setState(PLAYER_STATE state);
	void update(int x);
	void draw();
	void init(int x, int y);
	Player();
	~Player();
};