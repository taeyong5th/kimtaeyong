#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"
#include "BulletManager.h"
class TankManager;

class Tank : public GameObject
{
private:
	MOVE_STATE m_ePrevState;

	LPCWSTR m_aAnimations[16];
	LPCWSTR m_aShieldAnims[2];
	bool m_bAutoMode;
	bool m_bShieldOn;
	int m_iHP;
	int m_aAutoMode[9]; // �ڵ����� �����϶� ����� ����

	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // �����϶� �ִϸ��̼��� ���ʸ��� �ٲ�� ����
	float m_fBulletTick;
	float m_fShieldTick;
	float m_fShieldAnimTick;
	float m_fAutoMoveTick;

	int m_iAnimIndex = 0;
	int m_iShiledAnimIndex = 0;
	int m_iAutoIndex = 0;

	LPCWSTR getShape() override; // �׷��� ����� ��ȯ�Ѵ�.	
	BulletManager m_BulletManager; // �� ��ũ�� �� �Ѿ˵�
	
public:
	const float multifly = 1.0f;
	void init(int x, int y, RECT mapRect) override;
	void draw() override;
	POINT update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks); // tank ��ġ�� ������Ʈ�Ѵ�. 
	RECT getRect() override;
	bool setAutoMode(bool autoMode); // tank�� �ڵ����� �������� �����Ѵ�.
	bool setShield(bool shieldOn);
	int getHP();
	void setHP(int hp);
	
	void shootBullet();
	Tank();
	~Tank();
};