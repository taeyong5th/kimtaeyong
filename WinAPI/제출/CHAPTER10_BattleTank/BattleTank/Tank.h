#pragma once
#include "GlobalDefine.h"
#include "GameObject.h"
#include "BulletManager.h"

class Astar;
class TankManager;

class Tank : public GameObject
{
private:
	MOVE_STATE m_ePrevState;

	LPCWSTR m_aAnimations[16];
	LPCWSTR m_aShieldAnims[2];
	bool m_bAutoMode; // 자동으로 움직이는지
	bool m_bHoming; // 적을 추적하는지
	bool m_bShieldOn;
	int m_iHP;
	int m_aAutoMode[9]; // 자동으로 움직일때 사용할 값들

	//타임체크용
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fAnimTick; // 움직일때 애니메이션을 몇초마다 바뀌게 할지
	float m_fBulletTick;
	float m_fShieldTick;
	float m_fShieldAnimTick;
	float m_fAutoMoveTick;

	int m_iAnimIndex = 0;
	int m_iShiledAnimIndex = 0;
	int m_iAutoIndex = 0;

	LPCWSTR getShape() override; // 그려질 모양을 반환한다.	
	BulletManager m_BulletManager; // 이 탱크가 쏜 총알들
	
public:
	const float multifly = 1.0f;
	void init(int x, int y, RECT mapRect) override;
	void draw() override;
	POINT update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks); // tank 위치를 업데이트한다. 
	POINT getPOS();
	RECT getRect() override;
	bool setAutoMode(bool autoMode); // tank가 자동으로 움직일지 설정한다.
	bool setHoming(bool homingMode); // tank가 자동으로 적을 추적할지 설정한다.
	bool setShield(bool shieldOn);
	int getHP();
	void setHP(int hp);
	
	void shootBullet();
	Tank();
	~Tank();
};