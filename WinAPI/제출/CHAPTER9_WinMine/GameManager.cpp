#include "GameManager.h"

GameManager::GameManager()
{	
	srand(time(NULL));
	for (int i = 0; i < MAP_WIDTH_MAX; i++)
	{
		for (int j = 0; j < MAP_HEIGHT_MAX; j++)
		{
			m_Map[i][j] = nullptr;
		}
	}
	init(GAME_LEVEL_EASY);
}

GameManager::~GameManager()
{
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			if(m_Map[i][j] != NULL)
				delete m_Map[i][j];
		}
	}
}

void GameManager::initResource(HWND hWnd)
{
	m_hWnd = hWnd;
	HDC hdc = GetDC(hWnd);

	// ��Ʈ�� �̹��� �ε�
	BitmapManager::GetInstance()->init(hdc, 1000, 1000);
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_2));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_3));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_4));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_5));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_6));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_7));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_8));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_MINE));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_FLAG));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BG));
	
	ReleaseDC(hWnd, hdc);
}

void GameManager::start()
{	
	// ���ӽð� ���
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	if (m_eGameState == GAME_PLAY)
	{
		m_fGameTime += m_fDeltaTime;		
	}
	if (m_bClickable == false)
	{
		m_fClickTime += m_fDeltaTime;
	}
	if (m_fClickTime > 0.2f)
	{
		m_fClickTime = 0.0f;
		m_bClickable = true;
	}

	//Ŭ��
	POINT pt;
	int x = -1, y = -1;
	//���콺 ����Ʈ�� ��ǥ�� �����´�.
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);
	
	if ((pt.x > m_iLeft) && (pt.y > m_iTop))
	{
		x = (pt.x - m_iLeft) / 26;
		y = (pt.y - m_iTop) / 26;
	}

	// x, y�� ����ã�� �迭�� �������̸�
	if (isValidRange(x, y) && m_eGameState == GAME_PLAY && m_bClickable)
	{		
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			// �÷��� ���� ������ ����
			if (!m_Map[x][y]->isFlag())
			{
				// �ش� ��ġ�� ����.
				openMine(x, y);
			}
			// ���ڸ� �����ϸ� ���� ����
			if (m_Map[x][y]->getData() == MINE)
			{
				m_eGameState = GAME_OVER;
				MessageBox(m_hWnd, L"Game Over", L"Game Over", MB_OK);
				// ��� �� ����
				for (int i = 0; i < m_iRowCount; i++)
				{
					for (int j = 0; j < m_iColCount; j++)
					{
						m_Map[i][j]->open();
					}
				}

			}
			m_bClickable = false;
		}
		else if (GetKeyState(VK_RBUTTON) & 0x8000)
		{
			bool flag = m_Map[x][y]->setFlag();
			if (flag == true)
			{
				m_iFlagCount++;
			}
			m_bClickable = false;
		}		
	}

	float bgRate[4] = {0.0f, 0.4f, 0.6f, 1.0f};
	
	// ��� �׸���
	int bgWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getWidth(); // ���� ��Ʈ�� �̹��� ����
	int bgHeight = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getHeight(); // ���� ��Ʈ�� �̹��� ����
	int blockWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK)->getWidth(); // ���ں��Ѱ� ��Ʈ�� ����
	int blockHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK)->getHeight(); // ���ں��Ѱ�  ��Ʈ�� ����
	int bgRealWidth = blockWidth * m_iRowCount + 90; // ����� ���� ȭ�鿡 �׷��� ũ��
	int bgRealHeight = blockHeight * m_iColCount + 90;

	// ��� �κ� 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, 0, 1.0f, 1.0f, bgRate[0], bgRate[0], bgRate[1], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1], 0, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])), 1.0f, bgRate[1], bgRate[0], bgRate[2], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), 0, 1.0f, 1.0f, bgRate[2], bgRate[0], bgRate[3], bgRate[1]);

	// �߾� �κ�	
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, bgHeight * bgRate[1], 1.0f, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])), bgRate[0], bgRate[1], bgRate[1], bgRate[2]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), bgHeight * bgRate[1], 1.0f, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])), bgRate[2], bgRate[1], bgRate[3], bgRate[2]);

	// �ϴ� �κ� 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), 1.0f, 1.0f, bgRate[0], bgRate[2], bgRate[1], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1], bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])), 1.0f, bgRate[1], bgRate[2], bgRate[2], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), 1.0f, 1.0f, bgRate[2], bgRate[2], bgRate[3], bgRate[3]);

	// �� �׸���
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			m_Map[i][j]->draw(m_iLeft, m_iTop);
		}
	}

	// ���� ȭ�鿡 �׸���.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	// �ؽ�Ʈ ���
	static TCHAR tempstr[128];
	wsprintf(tempstr, TEXT("%d"), (int)m_fGameTime);
	TextOut(hdc, 135, bgRealHeight - 30, tempstr, lstrlen(tempstr));
	wsprintf(tempstr, TEXT("%d"), m_iMineCount - m_iFlagCount);
	TextOut(hdc, bgRealWidth - 155, bgRealHeight - 30, tempstr, lstrlen(tempstr));
	ReleaseDC(m_hWnd, hdc);

	// �̱�� ���� ����
	if (m_eGameState == GAME_PLAY && isWin())
	{
		m_eGameState = GAME_OVER;
		MessageBox(m_hWnd, L"Game Clear", L"Game Clear", MB_OK);
	}
}

void GameManager::init(GAME_LEVEL gameLevel, int col, int row, int mineCount)
{	
	m_eGameState = GAME_PLAY;
	// ���̵��� �� ũ�� ����
	switch (gameLevel)
	{
	case GAME_LEVEL_EASY:
		m_iRowCount = MAP_WIDTH_MIN;
		m_iColCount = MAP_HEIGHT_MIN;
		m_iMineMax = 10;
		break;
	case GAME_LEVEL_NORMAL:
		m_iRowCount = m_iColCount = 20;
		m_iMineMax = 25;
		break;
	case GAME_LEVEL_HARD:
		m_iRowCount = MAP_WIDTH_MAX;
		m_iColCount = MAP_HEIGHT_MAX; 
		m_iMineMax = 80;
		break;
	case GAME_LEVEL_USER:
		col = col < MAP_WIDTH_MAX ? col : MAP_WIDTH_MAX;
		col = col > MAP_WIDTH_MIN ? col : MAP_WIDTH_MIN;
		row = row < MAP_HEIGHT_MAX ? row : MAP_HEIGHT_MAX;
		row = row > MAP_HEIGHT_MIN ? row : MAP_HEIGHT_MIN;
		mineCount = mineCount < (col - 1) * (row - 1) ? mineCount : (col - 1) * (row - 1);
		mineCount = mineCount > 10 ? mineCount : 10;

		m_iRowCount = col;
		m_iColCount = row;
		m_iMineMax = mineCount;
		break;
	case GAME_LEVEL_AUTO:
		break;
	default:
		break;
	}

	// ������ ũ�� �缳��
	SetWindowPos(m_hWnd, 0, 0, 0, 26 * m_iRowCount + 100, 26 * m_iColCount + 150, SWP_NOMOVE | SWP_NOZORDER);

	// ���� �� �ʱ�ȭ
	for (int i = 0; i < MAP_WIDTH_MAX; i++)
	{
		for (int j = 0; j < MAP_HEIGHT_MAX; j++)
		{
			if (m_Map[i][j] != nullptr)
			{
				delete m_Map[i][j];
				m_Map[i][j] = nullptr;
			}				
		}
	}
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			m_Map[i][j] = new Block(i, j);
		}
	}

	// ���� �����
	m_iMineCount = 0;
	while (m_iMineCount < m_iMineMax)
	{
		int x = rand() % m_iRowCount;
		int y = rand() % m_iColCount;
		if (m_Map[x][y]->getData() != MINE)
		{
			m_Map[x][y]->setData(MINE);
			m_iMineCount++;
		}
	}

	// ���� ���� ����
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			if (m_Map[i][j]->getData() != MINE)
			{
				int count = countMine(i, j);
				m_Map[i][j]->setData(count);
			}
		}
	}

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fGameTime = 0.0f;
	m_fClickTime = 0.0f;
	m_bClickable = true;
	m_iFlagCount = 0;
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
			if (x < 0 || x > m_iRowCount - 1 || y < 0 || y > m_iColCount - 1) continue;
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
	// ���� ����ų� �̹� ���������� ����
	if (i < 0 || i >= m_iRowCount || j < 0 || j >= m_iColCount) return;	
	if (m_Map[i][j]->isOpen() == true) return;

	
	if (m_Map[i][j]->getData() == MINE)
	{
		m_Map[i][j]->open();
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
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			if (m_Map[i][j]->isOpen() && m_Map[i][j]->getData() != MINE)
			{
				count++;
			}
		}
	}

	// ���ڸ� �����ϰ� ���� �������� �¸�
	if (count + m_iMineCount == m_iRowCount * m_iColCount)
		return true;
	else
		return false;
}

bool GameManager::isValidRange(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= m_iRowCount) return false;
	if (y >= m_iColCount) return false;
	return true;
}
