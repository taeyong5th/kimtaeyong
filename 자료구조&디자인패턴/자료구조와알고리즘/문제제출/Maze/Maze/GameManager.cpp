#include "GameManager.h"

void GameManager::start()
{
	char mapdata[10][15] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 'x', 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1,
		1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1,
		1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1,
		1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 'y', 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

	PointType type;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (mapdata[i][j] == 1)
			{
				//m_MapDraw.DrawPoint("¡Ú", j, i);
				type = WALL;
			}
			else if(mapdata[i][j] == 'x')
			{
				type = CHARACTER;
			}
			else if (mapdata[i][j] == 'y')
			{
				type = GOAL;
			}
			else
			{
				type = EMPTY;
			}

			Point *point = createPoint(j, i, type);
			LInsert(&m_MapDataList, point);
		}
	}


	Point *p;
	if (LFirst(&m_MapDataList, &p))
	{
		while (LNext(&m_MapDataList, &p))
		{

		}
	}
	printf("\n");


	
	char key;
	while (true)
	{
		if (kbhit())
		{
			key = getch();
			switch (key)
			{
			default:
				m_MapDraw.BoxDraw(0, 0, MAP_SIZE_WIDTH, MAP_SIZE_HEIGHT);
				printf("%d", key);
			}
		}
	}
}

GameManager::GameManager()
{
	string cmd = "mode con cols=" + to_string(WINDOW_SIZE_WIDTH) + " lines=" + to_string(WINDOW_SIZE_HEIGHT);
	system(cmd.c_str());

	ListInit(&m_MapDataList);
}

GameManager::~GameManager()
{
}
