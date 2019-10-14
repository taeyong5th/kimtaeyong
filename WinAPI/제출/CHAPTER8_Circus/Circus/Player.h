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
	
	float m_fMoveAnimTick; // �����϶� �ִϸ��̼��� ���ʸ��� �ٲ�� ����
	float m_fJumpTick; // ���� ����
	float m_fWinAnimTick;
	int m_iWinAnimCount;
	int animCount = 0;
	
	RECT getPlayerRect();
	RECT getLionRect();
public:
	// ������Ʈ�� x, y �ʱ� ��ġ�� ���Ѵ�.
	void init(int x, int y) override;
	// camera�� X��ġ�� ���� ȭ����� ��ġ�� �ٽ� ���Ѵ�.
	void update(int camera_x = 0) override;
	// ��Ʈ�� �Ŵ����� Memory DC�� �׸���.
	void draw() override;

	void setPosition(int player_x);
	void setState(PLAYER_STATE state);

	Player();
	~Player();
};