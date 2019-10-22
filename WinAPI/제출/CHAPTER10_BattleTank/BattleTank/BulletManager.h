#pragma once
#include "GlobalDefine.h"
#include "Bullet.h"
#include "Block.h"
#include <list>

class TankManager;

class BulletManager
{
private:
	std::list<Bullet> m_BulletList;

public:
	void add(Bullet b);
	void update(Block* map[][MAP_HEIGHT], TankManager* enemyTanks);
	void draw();
	void clear();
	BulletManager();
	~BulletManager();
};


