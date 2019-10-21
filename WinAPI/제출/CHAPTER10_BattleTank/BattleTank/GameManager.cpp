#include "GameManager.h"

GameManager::GameManager()
{	
	srand(time(NULL));
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			m_Map[i][j] = nullptr;
		}
	}
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

	// 비트맵 이미지 로드
	BitmapManager::GetInstance()->init(hdc, 860*2, 800*2);
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BG));
	
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_BLANK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_A));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_U));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_L));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_D));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_R));		
		
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_GRAY));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_FOREST));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_WATER));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_A_HARD));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_U_HARD));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_L_HARD));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_D_HARD));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_R_HARD));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_MARK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLOCK_FLAG));
		
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_D0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_D1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_L0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_L1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_U0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_U1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_R0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ENEMY_TANK_R1));	
		
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_D0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_D1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_L0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_L1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_U0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_U1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_R0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_PLAYER_TANK_R1));
	
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_SHIELD_0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_SHIELD_1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_EXPLOSION_0));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_EXPLOSION_1));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_EXPLOSION_2));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_EXPLOSION_3));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_EXPLOSION_4));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ICON_PLAYER));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ICON_ENEMY));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ICON_STAGE));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BULLET_D));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BULLET_U));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BULLET_L));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BULLET_R));
	
	ReleaseDC(hWnd, hdc);
}

void GameManager::loadStage()
{
	HANDLE hFile = CreateFile(TEXT("stages//1.txt"), GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		for (int i = 0; i < m_iRowCount; i++)
		{
			for (int j = 0; j < m_iColCount; j++)
			{
				DWORD writeB;
				TCHAR data;
				ReadFile(hFile, &data, sizeof(TCHAR), &writeB, NULL);
				m_Map[i][j]->setData((BLOCK_TYPE(data - 'A')));
			}
		}
		CloseHandle(hFile);
	}
}

void GameManager::update()
{
	switch (m_eState)
	{
	case GAME_INTRO:
		gameIntro();
		break;
	case GAME_PLAY:
		gamePlay();
		break;
	case GAME_OVER:
		gameOver();
		break;
	case GAME_CLEAR:
		gameClear();
		break;
	}
}

void GameManager::initGame()
{
	m_eState = GAME_INTRO;
	m_iRowCount = MAP_WIDTH;
	m_iColCount = MAP_HEIGHT;

	// 맵 초기화
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
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
			m_Map[i][j] = new Block(m_MapRect.left + i * m_iBlockWidth, m_MapRect.top + j * m_iBlockHeight);
			m_Map[i][j]->init();
		}
	}

	// 맵 크기 정보 초기화
	m_iBlockWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth();
	m_iBlockHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight();
	m_MapRect.top = 40;
	m_MapRect.left = 39;
	m_MapRect.bottom = m_iBlockHeight * m_iColCount + 40;
	m_MapRect.right = m_iBlockWidth * m_iRowCount + 39;

	// 플레이어 초기화
	m_Player.init(0, 0, m_MapRect);
	m_Player.setTeam(TEAM_ALLY);

	m_iEnemyCount = 6;
	m_iStage = 1;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fEnemyGenTime = 0.0f;
}


void GameManager::gameIntro()
{
	// enter키를 누르면 플레이한다.
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		initGame();
		loadStage();
		for (int i = 0; i < m_iRowCount; i++)
		{
			for (int j = 0; j < m_iColCount; j++)
			{
				if (m_Map[i][j]->getData() == BLOCK_TYPE_BLANK)
				{
					m_iPlayerX = i * m_iBlockWidth + m_MapRect.left;
					m_iPlayerY = j * m_iBlockHeight + m_MapRect.top;
				}
			}
		}
		m_eState = GAME_PLAY;
	}
}

void GameManager::gamePlay()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fEnemyGenTime += m_fDeltaTime;

	// 키를 누르면 움직인다.
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_iPlayerX -= PLAYER_SPEED * m_fDeltaTime;
		m_Player.setState(MOVE_STATE_LEFT);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_iPlayerX += PLAYER_SPEED * m_fDeltaTime;
		m_Player.setState(MOVE_STATE_RIGHT);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		m_iPlayerY -= PLAYER_SPEED * m_fDeltaTime;
		m_Player.setState(MOVE_STATE_UP);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_iPlayerY += PLAYER_SPEED * m_fDeltaTime;
		m_Player.setState(MOVE_STATE_DOWN);
	}
	else
	{
		//m_Player.setState(PLAYER_STATE_IDLE);
	}

	//static int test[] = { 0, 1, 2, 3, 4, 4, 4, 4, 4 };
	//static int t = 2;
	//switch (test[t])
	//{
	//case 0:
	//	m_iPlayerX -= PLAYER_SPEED * m_fDeltaTime;
	//	m_Player.setState(MOVE_STATE_LEFT);
	//	break;
	//case 1:
	//	m_iPlayerX += PLAYER_SPEED * m_fDeltaTime;
	//	m_Player.setState(MOVE_STATE_RIGHT);
	//	break;
	//case 2:
	//	m_iPlayerY -= PLAYER_SPEED * m_fDeltaTime;
	//	m_Player.setState(MOVE_STATE_UP);
	//	break;
	//case 3:
	//	m_iPlayerY += PLAYER_SPEED * m_fDeltaTime;
	//	m_Player.setState(MOVE_STATE_DOWN);
	//	break;
	//case 4:
	//	m_Player.shootBullet();
	//	t = rand() % 9;
	//	break;
	//}

	//// 적을 생성한다.
	//if (m_fEnemyGenTime > 1.0f)
	//{
	//	m_fEnemyGenTime = 0.0f;
	//	t = rand() % 9;
	//	m_Player.shootBullet();
	//}

	m_Player.update(m_iPlayerX, m_iPlayerY, m_Map);

	// 블럭과의 충돌을 검사하고 위치를 보정한다.
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			RECT rect;
			// 플레이어와 충돌시 위치 보정
			if (IntersectRect(&rect, &m_Map[i][j]->getRect(), &m_Player.getRect()))
			{
				switch (m_Player.getState())
				{
				case MOVE_STATE_IDLE:
					break;	
				case MOVE_STATE_LEFT:
					m_iPlayerX = rect.right;
					break;
				case MOVE_STATE_RIGHT:
					m_iPlayerX = rect.left - m_iBlockWidth;
					break;
				case MOVE_STATE_UP:
					m_iPlayerY = rect.bottom;
					break;
				case MOVE_STATE_DOWN:
					m_iPlayerY = rect.top - m_iBlockHeight;
					break;
				default:
					break;
				}
				m_Player.update(m_iPlayerX, m_iPlayerY, m_Map);
			}
		}
	}

	// 스페이스를 누르면 총알을 발사한다.
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_Player.shootBullet();
	}

	// 화면을 그린다.
	draw();
}

void GameManager::gameOver()
{
}

void GameManager::gameClear()
{
}

void GameManager::draw()
{
	float bgRate[4] = { 0.0f, 0.4f, 0.6f, 1.0f };
	float multifly = 1.0f;
	// 배경 그리기
	int bgWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getWidth(); // 실제 비트맵 이미지 가로
	int bgHeight = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getHeight(); // 실제 비트맵 이미지 세로
	int blockWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth(); // 블럭한개 비트맵 가로
	int blockHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight(); // 블럭한개  비트맵 세로
	int bgRealWidth = blockWidth * m_iRowCount + (m_MapRect.left << 1); // 배경이 실제 화면에 그려질 크기
	int bgRealHeight = blockHeight * m_iColCount + (m_MapRect.top << 1);

	// 상단 부분 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, 0, multifly, multifly, bgRate[0], bgRate[0], bgRate[1], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1] * multifly, 0, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])) * multifly, multifly, bgRate[1], bgRate[0], bgRate[2], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2])) * multifly, 0, multifly, multifly, bgRate[2], bgRate[0], bgRate[3], bgRate[1]);

	// 중앙 부분	
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, (bgHeight * bgRate[1]) * multifly, multifly, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])) * multifly, bgRate[0], bgRate[1], bgRate[1], bgRate[2]);
	BitmapManager::GetInstance()->prepare(IMG_BG, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2])) * multifly, bgHeight * bgRate[1] * multifly, multifly, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])) * multifly, bgRate[2], bgRate[1], bgRate[3], bgRate[2]);

	// 하단 부분 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2])) * multifly, multifly, multifly, bgRate[0], bgRate[2], bgRate[1], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1] * multifly, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2])) * multifly, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])) * multifly, multifly, bgRate[1], bgRate[2], bgRate[2], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2])) * multifly, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2])) * multifly, multifly, multifly, bgRate[2], bgRate[2], bgRate[3], bgRate[3]);

	// 맵 그리기
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			m_Map[i][j]->draw();
		}
	}

	// 플레이어 그리기
	m_Player.draw();
	
	
	// 실제 화면에 그린다.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);

	// 맵 그리기
	/*for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			RECT rect = m_Map[i][j]->getRect();
			FillRect(hdc, &rect, nullptr);

		}
	}*/
	ReleaseDC(m_hWnd, hdc);
}

bool GameManager::isValidRange(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= m_iRowCount) return false;
	if (y >= m_iColCount) return false;
	return true;
}
