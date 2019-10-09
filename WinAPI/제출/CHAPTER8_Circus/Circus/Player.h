#pragma once
#include "GameDefine.h"

enum PLAYER_STATE
{
	PLAYER_STATE_IDLE,
	PLAYER_STATE_MOVE,
	PLAYER_STATE_JUMP,
	PLAYER_STATE_DIE
};


class Player
{
private:
	int m_ix, m_iy; // ĳ���Ͱ� �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	const float multiple = 2.0f; // ���� �̹����� �� ��ũ��� �׸���	
	PLAYER_STATE m_eState;

	LPCWSTR moveAnimation[3];

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fMoveAnimTick; // �����϶� �ִϸ��̼��� ���ʸ��� �ٲ�� ����
	float m_fJumpTick; // ���� ����
public:
	void setState(PLAYER_STATE state);
	void update(int x, int y);
	void init(int x, int y);
	Player();
	~Player();
};