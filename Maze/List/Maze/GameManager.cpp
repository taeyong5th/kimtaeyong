#include "GameManager.h"

void GameManager::printMap()
{

	for (int i = 0; i < m_MapDataList.size(); i++)
	{
		for (list<Point>::iterator iter = m_MapDataList[i].begin(); iter != m_MapDataList[i].end(); ++iter)
		{
			switch (iter->type)
			{
			case WALL:
				m_MapDraw.DrawPoint("��", iter->x, iter->y);
				break;
			case GOAL:
				m_MapDraw.DrawPoint("��", iter->x, iter->y);
				break;
			case EMPTY:
				m_MapDraw.DrawPoint("  ", iter->x, iter->y);
				break;
			}
		}
	}
}

void GameManager::printCharacter()
{
	m_MapDraw.DrawPoint("��", m_characterPos.x, m_characterPos.y);
}

// ĳ���͸� �̵��Ѵ�.
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

	int x = (m_characterPos.x + moveX);
	int y = (m_characterPos.y + moveY);

	// �̵��� ��ġ�� �� ���� �ȿ� ������,
	if ((0 <= x && x < MAP_SIZE_WIDTH) && (0 <= y && y < MAP_SIZE_HEIGHT))
	{
		// x, y ��ġ�� iter�� ���Ѵ�.
		list<Point>::iterator iter = m_MapDataList[y].begin();
		for (int i = 0; i < x; ++i)
		{
			++iter;
		}
		
		// x, y ��ġ�� ���� �ƴϸ� �̵���Ų��.
		if (iter->type != WALL)
		{
			m_characterPos.x = x;
			m_characterPos.y = y;
		}
	}
}

// ��ǥ ������ �����ߴ��� Ȯ���Ѵ�.
bool GameManager::isClear()
{
	if ((m_characterPos.x == m_GoalPos.x) && (m_characterPos.y == m_GoalPos.y))
		return true;

	return false;
}

void GameManager::init()
{
	//  �� ������ �б�
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
	
	// ����Ʈ �ʱ�ȭ
	PointType type;	
	for (int i = 0; i < MAP_SIZE_HEIGHT; i++)
	{
		list<Point> list;
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

			//Point* point = createPoint(j, i, type);
			//LInsert(&m_MapDataList, point);
			Point point = {j, i, type};
			list.push_back(point);
		}
		m_MapDataList.push_back(list);
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

			// ĳ���� �̵� �� ���
			moveCharacter(key);
			printCharacter();
			// Ŭ�����ϸ� ����
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

	//ListInit(&m_MapDataList);
	init();
}

GameManager::~GameManager()
{
}
