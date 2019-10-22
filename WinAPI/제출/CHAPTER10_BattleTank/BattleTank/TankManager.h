#pragma once
#include "GlobalDefine.h"
#include "Tank.h"
#include "Block.h"
#include <list>

class TankManager
{
private:
	std::list<Tank> m_TankList;
public:
	void add(Tank b);
	void update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks);
	void draw();
	void clear();
	int size();
	bool isCollision(RECT bulletRect);
	void setState(MOVE_STATE state);
	void shootBullet();
	std::list<Tank>::iterator begin();
	TankManager();
	~TankManager();
};


