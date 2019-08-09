#include "GameManager.h"

GameManager::GameManager()
{	
	setConsoleSize();
	m_iWidth = MAP_SIZE_WIDTH;
	m_iHeight = MAP_SIZE_HEIGHT;
	m_foods = NULL;
	m_walls = NULL;
	srand(time(NULL));
}

GameManager::~GameManager()
{
	release();
}

void GameManager::init()
{
	m_iScore = 0;
	
	int positionY = m_iHeight * 0.2;
	m_MapDraw.DrawMidText("                 ", m_iWidth, positionY);
	m_MapDraw.DrawMidText("                 ", m_iWidth, positionY + 2);
	m_MapDraw.DrawMidText("                 ", m_iWidth, positionY + 4);
	m_MapDraw.DrawMidText("                 ", m_iWidth, positionY + 6);

	m_Snake.init(m_iWidth / 2, m_iHeight / 2);
	m_Snake.draw();
}

void GameManager::release()
{
	if (m_foods != NULL)
	{
		removeAllBlock(m_foods);
		m_foods = NULL;
	}
	if (m_walls != NULL)
	{
		removeAllBlock(m_walls);
		m_walls = NULL;
	}
	m_Snake.release();
}

void GameManager::start()
{
	int positionY = m_iHeight * 0.2;
	m_MapDraw.BoxDraw(0, 0, m_iWidth, m_iHeight, true);
	m_MapDraw.DrawMidText("�� Snake Game ��", m_iWidth, positionY);
	m_MapDraw.DrawMidText("1. ���� ����", m_iWidth, positionY + 2);
	m_MapDraw.DrawMidText("2. ���� ����", m_iWidth, positionY + 4);
	m_MapDraw.DrawMidText("�Է� : ", m_iWidth, positionY + 6);
	m_MapDraw.gotoxy(m_iWidth + 6, positionY + 6);

	while (true)
	{
		int menuSelect;
		cin >> menuSelect;
		switch (menuSelect)
		{
		case MAIN_MENU_PLAY:
			init();
			return play();
		case MAIN_MENU_EXIT:
			return;
		default:
			return start();
		}
	}
}

void GameManager::play()
{
	printSocre(m_iScore);
	clock_t foodClock, snakeClock;
	clock_t curClock;
	snakeClock = foodClock = clock();
	
	// ��ֹ��� �����.
	while (countBlock(m_walls) < WALL_COUNT) 
	{
		addBlock(&m_walls, makeBlock(BLOCK_STATE_WALL));
	}

	while (true)
	{
		// key �Է� ó��
		if (kbhit()) {
			char key = getch();
			switch (key)
			{
			case KEY_LEFT: // left
				m_Snake.setDirection(DIRECTION_LEFT);
				break;
			case KEY_RIGHT: // right
				m_Snake.setDirection(DIRECTION_RIGHT);
				break;
			case KEY_UP: // up
				m_Snake.setDirection(DIRECTION_UP);
				break;
			case KEY_DOWN: // down
				m_Snake.setDirection(DIRECTION_DOWN);
				break;
			default:
				break;
			}
		}
		
		curClock = clock();

		// ������ �����.
		if (curClock - foodClock > SNAKE_CREATE_FOOD_INTERVAL)
		{
			// ������ �ִ� ������ŭ�� ����
			if (countBlock(m_foods) < FOOD_MAX) 
			{
				addBlock(&m_foods, makeBlock(BLOCK_STATE_FOOD));
			}
			foodClock = clock();
		}

		// ���� �̵� ��Ų��.
		if (curClock - snakeClock > m_Snake.getSpeed())
		{			
			Block* food = getBlock(m_foods, m_Snake.getX(), m_Snake.getY());
			Block* wall = getBlock(m_walls, m_Snake.getX(), m_Snake.getY());
			
			// �ڱ� �ڽ� or �� �׵θ� or ��ֹ��� �΋H���� ��
			if (m_Snake.isSelfCollision() || isMapCollision(m_Snake.getX(), m_Snake.getY()) || wall != NULL)
			{
				return gameOver();
			}
			// ������ ������ �Դ´�
			else if(food != NULL)
			{
				m_Snake.action(SNAKE_ACTION_EAT); // ������ �Դ´�.
				removeBlock(&m_foods, food); // ���� ���� �����.
				m_Snake.speedUp(); // �ӵ��� ������Ų��.
				printSocre(++m_iScore); // ������ ������Ų��.				
			}			
			// ������ ������ �������� �����δ�.
			else if (m_Snake.getDirection() != DIRECTION_NONE)
			{
				m_Snake.action(SNAKE_ACTION_MOVE); // �����δ�.
			}
			else
			{
				m_Snake.action(SNAKE_ACTION_WAIT); // ����Ѵ�.
			}
			snakeClock = clock();
		}
	}
}

void GameManager::gameOver()
{
	m_MapDraw.BoxDraw(0, 0, m_iWidth, m_iHeight, true);
	m_MapDraw.DrawMidText("       G A M E O V E R       ", m_iWidth, 10);
	m_MapDraw.DrawMidText("       PRESS ANY KEY TO CONTINUE       ", m_iWidth, 13);
	release(); // �����Ҵ��� �޸𸮸� ��ȯ
	getch();
	start(); // ������ �ٽ� ����
}

void GameManager::printSocre(int score)
{
	m_MapDraw.DrawMidText("���� : " + to_string(score), m_iWidth, m_iHeight + 1);
}

bool GameManager::isMapCollision(int x, int y)
{
	if (x == 0) return true;
	else if (y == 0) return true;
	else if (y == MAP_SIZE_HEIGHT - 1) return true;
	else if (x == MAP_SIZE_WIDTH - 1) return true;
	else return false;
}

Block* GameManager::makeBlock(BLOCK_STATE state)
{
	int x = rand() % (m_iWidth - 2) + 1;
	int y = rand() % (m_iHeight - 2) + 1;

	// x, y ��ġ�� �̹� ����/��ֹ�/���� x, y ��ġ�� �ٽ� ����
	if (getBlock(m_foods, x, y) != NULL) return makeBlock(state);
	if (getBlock(m_walls, x, y) != NULL) return makeBlock(state);	
	if (m_Snake.isCollisiton(x, y) == true) return makeBlock(state);

	Block* newBlock = new Block(state, x, y);
	newBlock->draw();
	return newBlock;
}

void GameManager::removeBlock(Block** head, Block* block)
{
	// ������ block�� head �̸� head�� ���� block���� ����
	if (*head == block)
	{
		*head = (*head)->nextBlock;		
	}
	// head�� �ƴϸ� ������ �� ���� ���� ã�Ƽ� ���� ���� ���� �� ����
	else
	{
		Block* prev = *head;
		while (prev->nextBlock != block)
		{
			prev = prev->nextBlock;
		}
		prev->nextBlock = block->nextBlock;		
	}
	delete block;
}

void GameManager::removeAllBlock(Block* head)
{
	if (head == NULL) return;
	removeAllBlock(head->nextBlock);
	delete head;
}

Block* GameManager::getBlock(Block* head, int x, int y)
{
	Block* temp = head;
	while (temp != NULL)
	{
		if (temp->getX() == x && temp->getY() == y)
			return temp;
		temp = temp->nextBlock;
	}

	return NULL;
}

void GameManager::addBlock(Block** head, Block* block)
{
	// ����� NULL �̸� head�� �߰�
	if (*head == NULL)
	{
		*head = block;
	}
	// �� block�� ����Ʈ�� ���� �տ� �߰�
	else
	{
		block->nextBlock = *head;
		*head = block;
	}
}

int GameManager::countBlock(Block* head)
{
	int count = 0;
	Block* temp = head;
	while (temp != NULL)
	{
		temp = temp->nextBlock;
		count++;
	}
	return count;
}

void GameManager::setConsoleSize(int width, int height)
{
	string command = "mode con cols=" + to_string(width) + " lines=" + to_string(height);
	system(command.c_str());
}
