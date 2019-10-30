#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Star.h"
#include "SingleTon.h"
#include <list>
class Flight;

class StarManager : public SingleTon<StarManager>
{
private:
	std::list<Star*> m_Stars;
	int m_iScore;

public:
	void init();
	void createBullet(JEngine::POINT flighitPoint);
	void draw();
	void update(float fETime, Flight& flight);

	StarManager();
	~StarManager();
};