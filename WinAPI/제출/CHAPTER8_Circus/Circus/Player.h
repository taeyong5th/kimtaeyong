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
	int m_ix, m_iy; // ĳ���Ͱ� �׷��� ��ġ(�»���� �ƴ� �߽���ġ)
	int m_iWidth, m_iHeight;
	const float m_iMultiple = 2.0f; // ���� �̹����� �� ��ũ��� �׸���	
	PLAYER_STATE m_eState;

	LPCWSTR m_aMoveAnimation[3];
	LPCWSTR m_aWinAnimation[2];

	RECT m_Rect; // �浹 ����
	
	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fMoveAnimTick; // �����϶� �ִϸ��̼��� ���ʸ��� �ٲ�� ����
	float m_fJumpTick; // ���� ����
public:
	RECT getRect();
	void setState(PLAYER_STATE state);
	void update(int x);
	void draw();
	void init(int x, int y);
	Player();
	~Player();
};