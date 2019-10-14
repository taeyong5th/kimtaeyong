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

class Player : public CircusObject
{
private:
	PLAYER_STATE m_eState;

	LPCWSTR m_aMoveAnimation[3];
	LPCWSTR m_aWinAnimation[2];
	
	float m_fMoveAnimTick; // 움직일때 애니메이션을 몇초마다 바뀌게 할지
	float m_fJumpTick; // 점프 동작
	float m_fWinAnimTick;
	int m_iWinAnimCount;
	int animCount = 0;
	
	RECT getPlayerRect();
	RECT getLionRect();
public:
	// 오브젝트의 x, y 초기 위치를 정한다.
	void init(int x, int y) override;
	// camera의 X위치에 따라 화면상의 위치를 다시 정한다.
	void update(int camera_x = 0) override;
	// 비트맵 매니저의 Memory DC에 그린다.
	void draw() override;

	void setPosition(int player_x);
	void setState(PLAYER_STATE state);

	Player();
	~Player();
};