#include "GameManager.h"

void GameManager::printMap()
{
	Point* p;
	if (LFirst(&m_MapDataList, &p))
	{
		switch (p->type)
		{
		case WALL:
			m_MapDraw.DrawPoint("■", p->x, p->y);
			break;
		case GOAL:
			m_MapDraw.DrawPoint("◎", p->x, p->y);
			break;
		case EMPTY:
			m_MapDraw.DrawPoint("  ", p->x, p->y);
			break;
		}
		while (LNext(&m_MapDataList, &p))
		{
			switch (p->type)
			{
			case WALL:
				m_MapDraw.DrawPoint("■", p->x, p->y);
				break;
			case GOAL:
				m_MapDraw.DrawPoint("◎", p->x, p->y);
				break;
			case EMPTY:
				m_MapDraw.DrawPoint("  ", p->x, p->y);
				break;
			}
		}
	}
}

void GameManager::printCharacter()
{
	m_MapDraw.DrawPoint("★", m_characterPos.x, m_characterPos.y);
}

// 캐릭터를 이동한다.
void GameManager::moveCharacter(int key)
{
	int moveX = 0;
	int moveY = 0;
	switch (key)
	{
	case KEY_UP:
		moveY = -1;
		break;
	case KEY_DOWN:
		moveY = 1;
		break;
	case KEY_LEFT:
		moveX = -1;
		break;
	case KEY_RIGHT:
		moveX = 1;
		break;
	default:
		break;
	}

	Point* p;
	if (LFirst(&m_MapDataList, &p))
	{
		while (LNext(&m_MapDataList, &p))
		{
			if ((p->x == m_characterPos.x + moveX) && (p->y == m_characterPos.y + moveY))
			{
				// 캐릭터가 이동할 벽이 아니면(비어 있으면) 이동
				if (p->type != WALL)
				{
					m_characterPos.x += moveX;
					m_characterPos.y += moveY;
					break;
				}
			}
		}
	}

}

// 목표 지점에 도달했는지 확인한다.
bool GameManager::isClear()
{
	if ((m_characterPos.x == m_GoalPos.x) && (m_characterPos.y == m_GoalPos.y))
		return true;

	return false;
}

void GameManager::init()
{
	//  맵 데이터 읽기
	char mapData[MAP_SIZE_HEIGHT][MAP_SIZE_WIDTH];

	ifstream mapFile("MapData.txt");
	char temp; 
	for (int i = 0; i < MAP_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_SIZE_WIDTH; j++)
		{
			mapFile >> temp;
			mapData[i][j] = temp;
		}
	}
	mapFile.close();
	
	// 리스트 초기화
	PointType type;
	for (int i = 0; i < MAP_SIZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_SIZE_WIDTH; j++)
		{
			if (mapData[i][j] == '1')
			{
				type = WALL;
			}
			else if (mapData[i][j] == 'x')
			{
				type = EMPTY;
				m_characterPos.x = j;
				m_characterPos.y = i;
				m_characterPos.type = CHARACTER;
			}
			else if (mapData[i][j] == 'y')
			{
				type = GOAL;
				m_GoalPos.x = j;
				m_GoalPos.y = i;
				m_GoalPos.type = GOAL;
			}
			else
			{
				type = EMPTY;
			}

			Point* point = createPoint(j, i, type);
			LInsert(&m_MapDataList, point);
		}
	}
}

void GameManager::start()
{
	printMap();
	printCharacter();

	char key;
	while (true)
	{
		if (kbhit())
		{
			printMap();
			key = getch();

			// 캐릭터 이동 후 출력
			moveCharacter(key);
			printCharacter();
			// 클리어하면 종료
			if (isClear())
			{
				m_MapDraw.DrawMidText("C L E A R !!", WINDOW_SIZE_WIDTH / 2, WINDOW_SIZE_HEIGHT / 2);
				break;
			}
		}
	}
}

GameManager::GameManager()
{
	string cmd = "mode con cols=" + to_string(WINDOW_SIZE_WIDTH) + " lines=" + to_string(WINDOW_SIZE_HEIGHT);
	system(cmd.c_str());

	ListInit(&m_MapDataList);
	init();
}

GameManager::~GameManager()
{
}
