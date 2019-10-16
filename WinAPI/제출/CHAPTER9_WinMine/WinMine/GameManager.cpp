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
	init(MAP_WIDTH_MAX, MAP_HEIGHT_MAX);
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

	

	//Ŭ��
	POINT pt;
	int x, y;
	//���콺 ����Ʈ�� ��ǥ�� �����´�.
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);
	x = (pt.x - m_iLeft) / 26;
	y = (pt.y - m_iTop) / 26;	

	// x, y�� ����ã�� �迭�� �������̸�
	if (isValidRange(x, y))
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
				MessageBox(m_hWnd, L"Game Over", L"Game Over", MB_OK);
			}
		}
		else if (GetKeyState(VK_RBUTTON) & 0x8000)
		{
			m_Map[x][y]->setFlag();
		}
	}
	
	// ��� �׸���
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, 0);
	// �� �׸���
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			m_Map[i][j]->draw(m_iTop, m_iLeft);
		}
	}

	// ���ӽð� ���
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fGameTime += m_fDeltaTime;

	// ���� ȭ�鿡 �׸���.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	// �ؽ�Ʈ ���
	static TCHAR tempstr[128];
	wsprintf(tempstr, TEXT("%d"), (int)m_fGameTime);
	TextOut(hdc, 500, 500, tempstr, lstrlen(tempstr));
	ReleaseDC(m_hWnd, hdc);

	// �̱�� ���� ����
	if (isWin())
	{
		MessageBox(m_hWnd, L"Game Clear", L"Game Clear", MB_OK);
	}
}

void GameManager::init(int rowCount, int colCount)
{
	m_iRowCount = rowCount < MAP_WIDTH_MAX ? rowCount : MAP_WIDTH_MAX;
	m_iColCount = colCount < MAP_HEIGHT_MAX ? colCount : MAP_HEIGHT_MAX;

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
			m_Map[i][j] = new Element(i, j);
		}
	}

	m_iMineMax = MINE_COUNT;
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
	if (x >= m_iRowCount) return false; 
	if (y < 0) return false;	
	if (y >= m_iRowCount) return false;
	return true;
}
