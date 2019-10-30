#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Bullet.h"
#include "SingleTon.h"
#include <list>
class Flight;

class BulletManager : public SingleTon<BulletManager>
{
private:
	std::list<Bullet*> m_Bullets;

public:
	void init();
	void createBullet(JEngine::POINT flighitPoint);
	void draw();
	void update(float fETime, Flight& flight);

	BulletManager();
	~BulletManager();
};