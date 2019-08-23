#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "GameDefine.h"
#include "DBLinkedList.h"

class GameManager
{
private:
	MapDraw m_MapDraw;
	List m_MapDataList;

public:
	void start();
	GameManager();
	~GameManager();

};