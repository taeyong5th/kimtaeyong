#include "GameManager.h"

GameManager::GameManager()
{
	string cmd = "mode con cols=" + to_string(WIDTH * 2 + 1) + " lines=" + to_string(HEIGHT + 5);
	system(cmd.c_str());
	srand(time(NULL));

	// 커서 설정
	m_Cursor.x = WIDTH / 2;
	m_Cursor.y = HEIGHT / 2;
	m_Cursor.shape = "♤";

	// 지뢰 맵 초기화
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			m_Map[i][j] = new Element(i, j);
		}
	}

	// 지뢰 만들기
	m_iMineCount = 0;
	while (m_iMineCount < MINE_COUNT)
	{
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		if (m_Map[x][y]->getData() != MINE)
		{
			m_Map[x][y]->setData(MINE);
			m_iMineCount++;
		}
	}
		
	// 지뢰 개수 세기
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{			
			if (m_Map[i][j]->getData() != MINE)
			{
				int count = countMine(i, j);
				m_Map[i][j]->setData(count);
			}
		}
	}

	// 맵 그리기
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			m_Map[i][j]->draw();
		}
	}

	printPlayInfo();
}

GameManager::~GameManager()
{
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if(m_Map[i][j] != NULL)
				delete m_Map[i][j];
		}
	}
}

void GameManager::start()
{	
	char key;	
	m_Mapdraw.DrawPoint(m_Cursor.shape, m_Cursor.x, m_Cursor.y);
	while (true)
	{
		if (kbhit())
		{
			key = getch();
			m_Map[m_Cursor.x][m_Cursor.y]->draw();
			switch (key)
			{
			case KEY_LEFT:
				m_Cursor.x--;
				break;
			case KEY_RIGHT:
				m_Cursor.x++;
				break;
			case KEY_DOWN:
				m_Cursor.y++;
				break;
			case KEY_UP:
				m_Cursor.y--;
				break;
			case KEY_ENTER:
				// 플래그 꽂혀 있으면 무시
				if (m_Map[m_Cursor.x][m_Cursor.y]->isFlag())
				{
					break;
				}
				// 지뢰를 선택하면 게임 종료
				if (m_Map[m_Cursor.x][m_Cursor.y]->getData() == MINE)
				{
					m_Mapdraw.DrawMidText("G A M E O V E R", WIDTH, HEIGHT / 2);
					Sleep(1000);
					return;
				}
				// 해당 위치를 연다.
				openMine(m_Cursor.x, m_Cursor.y);
				// 이기면 게임 종료
				if (isWin())
				{
					m_Mapdraw.DrawMidText("Y O U W I N", WIDTH, HEIGHT / 2);
					Sleep(1000);
					return;
				}
				break;
			case KEY_FLAG:
				// 플래그를 설정하고 다시 그린다.
				m_Map[m_Cursor.x][m_Cursor.y]->setFlag();
				m_Map[m_Cursor.x][m_Cursor.y]->draw();
				break;
			}
			// 커서가 범위 밖으로 나가면 위치를 보정하고 커서를 그린다.
			adjustCursorPosition();
			m_Mapdraw.DrawPoint(m_Cursor.shape, m_Cursor.x, m_Cursor.y);
		}
	}

}

void GameManager::adjustCursorPosition()
{
	if (m_Cursor.x < 0) m_Cursor.x = 0;
	if (m_Cursor.x > WIDTH - 1) m_Cursor.x = WIDTH - 1;
	if (m_Cursor.y < 0) m_Cursor.y = 0;
	if (m_Cursor.y > HEIGHT - 1) m_Cursor.y = HEIGHT - 1;
}

int GameManager::countMine(int i, int j)
{
	int count = 0;

	int row_start = (i - 1);
	int col_start = (j - 1);
	int row_end = (i + 2);
	int col_end = (j + 2);

	for (int x = row_start; x < row_end; x++)
	{
		for (int y = col_start; y < col_end; y++)
		{
			if (x < 0 || x > WIDTH - 1 || y < 0 || y > HEIGHT - 1) continue;
			if (m_Map[x][y]->getData() == MINE)
			{
				count++;
			}
		}
	}
	return count;
}

void GameManager::openMine(int i, int j)
{
	// 범위 벗어나거나 이미 열려있으면 종료
	if (i < 0 || i >= WIDTH || j < 0 || j >= HEIGHT) return;	
	if (m_Map[i][j]->isOpen() == true) return;

	
	if (m_Map[i][j]->getData() == MINE)
	{
		//m_Map[i][j]->open();
		return;
	}
	else if (m_Map[i][j]->getData() == 0)
	{
		m_Map[i][j]->open();
		openMine(i, j - 1);
		openMine(i, j + 1);
		openMine(i - 1, j);
		openMine(i + 1, j);
	}
	else if (m_Map[i][j]->getData() > 0)
	{
		m_Map[i][j]->open();
		return;
	}
	
}

bool GameManager::isWin()
{
	int count = 0;
	for (int i = 0; i < WIDTH; i++)
	{
		for (int j = 0; j < HEIGHT; j++)
		{
			if (m_Map[i][j]->isOpen() && m_Map[i][j]->getData() != MINE)
			{
				count++;
			}
		}
	}

	// 지뢰를 제외하고 전부 열었으면 승리
	if (count + m_iMineCount == WIDTH * HEIGHT)
		return true;
	else
		return false;
}

void GameManager::printPlayInfo()
{
	m_Mapdraw.DrawMidText("지뢰 개수 : " + to_string(m_iMineCount) + " 개", WIDTH, HEIGHT + 1);
	m_Mapdraw.DrawMidText("방향키 : A S D F ", WIDTH, HEIGHT + 2);
	m_Mapdraw.DrawMidText("열기 : ENTER   플래그 : .", WIDTH, HEIGHT + 3);
}
