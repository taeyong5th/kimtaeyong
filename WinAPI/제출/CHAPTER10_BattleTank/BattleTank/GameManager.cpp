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
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_INTRO));
	
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
	
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_ITEM));
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

void GameManager::loadStage(int stageNum)
{
	// stage 정보를 불러온다
	static TCHAR tempstr[128];
	wsprintf(tempstr, TEXT("stages//%d.txt"), stageNum);
	HANDLE hFile = CreateFile(tempstr, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
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

	// 불러온 맵에서 플레이어 위치를 랜덤으로 정한다.
	int i, j, x, y;
	while (true)
	{
		i = rand() % m_iRowCount;
		j = rand() % m_iColCount;
		//i = 3;
		//j = 4;
		if (m_Map[i][j]->getData() == BLOCK_TYPE_BLANK)
		{
			x = i * m_iBlockWidth + m_MapRect.left;
			y = j * m_iBlockHeight + m_MapRect.top;
			Tank player;
			player.init(0, 0, m_MapRect);
			player.setTeam(TEAM_ALLY);			
			player.init(x, y, m_MapRect);
			player.setHP(m_iPlayerHP);
			m_PlayerTank.add(player);
			break;
		}
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
	m_PlayerTank.clear();
	
	// 적 정보 초기화
	m_iEnemyCreaetedCount = 0;
	m_EnemyTanks.clear();

	// 아이템 초기화
	m_item.setPos(-100, -100);

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fEnemyGenTime = 0.0f;
	m_fItemGenTime = 0.0f;
	m_fPauseTime = 0.0f;
	m_iClearAnimCount = 0;
}

void GameManager::gameIntro()
{
	draw();
	// space키를 누르면 플레이한다.
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		initGame();
		m_iStageNum = 1;
		m_iPlayerHP = 5;
		loadStage(m_iStageNum);
		m_eState = GAME_PLAY;
	}
}

void GameManager::gamePlay()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fEnemyGenTime += m_fDeltaTime;
	m_fItemGenTime += m_fDeltaTime;

	// 키를 누르면 움직인다.
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_PlayerTank.setState(MOVE_STATE_LEFT);
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_PlayerTank.setState(MOVE_STATE_RIGHT);
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		m_PlayerTank.setState(MOVE_STATE_UP);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_PlayerTank.setState(MOVE_STATE_DOWN);
	}
	else
	{
		m_PlayerTank.setState(MOVE_STATE_IDLE);
	}
	// 스페이스를 누르면 총알을 발사한다.
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_PlayerTank.shootBullet();
	}

	// 2.2초마다 적을 생성한다.
	if (m_fEnemyGenTime > 2.2f)
	{
		m_fEnemyGenTime = 0.0f;
		addEnemy();
	}
	// 아이템을 생성한다.
	if (m_fItemGenTime > 9.0f)
	{
		m_fItemGenTime = 0.0f;
		generateItem();		
	}

	// 아이템 획득시 실드켜기
	if (m_PlayerTank.size() > 0 && m_PlayerTank.begin()->isCollision(m_item.getRect()))
	{		
		m_PlayerTank.begin()->setShield(true);
		m_item.setPos(-100, -100);
	}	

	m_PlayerTank.update(m_Map, &m_EnemyTanks);
	m_EnemyTanks.update(m_Map, &m_PlayerTank);


	// 화면을 그린다.
	draw();

	if (m_EnemyTanks.size() <= 0 && m_iEnemyCreaetedCount == ENEMY_MAX)
	{
		m_eState = GAME_CLEAR;
	}
	if (m_iPlayerHP <= 0)
	{
		m_eState = GAME_OVER;
	}
}

void GameManager::gameOver()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fPauseTime += m_fDeltaTime;

	if (m_fPauseTime > 2.0f)
	{
		m_fPauseTime = 0.0f;
		m_eState = GAME_INTRO;
	}
}

void GameManager::gameClear()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fPauseTime += m_fDeltaTime;

	// 클리어시 벽돌로 화면 채우는 애니메이션
	if (m_fPauseTime > 0.1f)
	{
		m_fPauseTime = 0.0f;

		int i = m_iClearAnimCount;
		int j = 0;
		if (m_iClearAnimCount >= m_iRowCount)
		{
			i = m_iRowCount - 1;
			j = m_iClearAnimCount % m_iRowCount;
		}
		for ( ; (i >= 0) && (j >= 0) && (i < m_iRowCount) && (j < m_iColCount) ; i--, j++)
		{
			m_Map[i][j]->setData(BLOCK_TYPE_A);
		}
		m_iClearAnimCount++;
	}

	draw();

	// 애니메이션이 끝나면 다음 스테이지
	if (m_iClearAnimCount >= (m_iRowCount + m_iColCount))
	{
		m_iStageNum++;
		if (m_iStageNum >= STAGE_MAX)
		{
			MessageBox(m_hWnd, TEXT("Clear!"), TEXT("Game Clear!"), MB_OK);
			m_eState = GAME_INTRO;
		}
		else
		{
			initGame();
			loadStage(m_iStageNum);
			m_eState = GAME_PLAY;
		}
	}
}

void GameManager::draw()
{
	TCHAR stageText[128] = TEXT("");
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

	switch (m_eState)
	{
	case GAME_INTRO:
		BitmapManager::GetInstance()->prepare(IMG_INTRO, m_MapRect.left, m_MapRect.top, 1.0f, 1.0f);
		wsprintf(stageText, TEXT("PRESS SPACEBAR TO START"));
		break;
	case GAME_PLAY:
		// 맵 그리기
		for (int i = 0; i < m_iRowCount; i++)
		{
			for (int j = 0; j < m_iColCount; j++)
			{
				m_Map[i][j]->draw();
			}
		}
		m_item.draw();

		// 플레이어 그리기
		m_PlayerTank.draw();
		m_EnemyTanks.draw();

		// 남은 적 수 그리기
		for (int i = 0; i < (ENEMY_MAX - m_iEnemyCreaetedCount); ++i)
		{
			BitmapManager::GetInstance()->prepare(IMG_ICON_ENEMY, bgRealWidth - 25, 10 + 15 * i);
		}

		// 남은 HP 그리기
		if (m_PlayerTank.size() > 0)
		{
			m_iPlayerHP = m_PlayerTank.begin()->getHP();
		}
		else
		{
			m_iPlayerHP = 0;
		}
		for (int i = 0; i < m_iPlayerHP; ++i)
		{
			BitmapManager::GetInstance()->prepare(IMG_ICON_PLAYER, 10, 10 + 15 * i);
		}
		
		wsprintf(stageText, TEXT("STAGE %d"), m_iStageNum);
		break;
	case GAME_OVER:
		
		break;
	case GAME_CLEAR:
		// 맵 그리기
		for (int i = 0; i < m_iRowCount; i++)
		{
			for (int j = 0; j < m_iColCount; j++)
			{
				m_Map[i][j]->draw();
			}
		}
		break;
	}
	
	// 실제 화면에 그린다.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);	
	TextOut(hdc, bgRealWidth / 2 - lstrlen(stageText)*4, bgRealHeight - 35, stageText, lstrlen(stageText));
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::addEnemy()
{
	if (m_iEnemyCreaetedCount < ENEMY_MAX)
	{
		int i, j, x, y;
		while (true)
		{
			i = rand() % m_iRowCount;
			j = rand() % m_iColCount;
			//i = 8;
			//j = 3;			
			if (m_Map[i][j]->getData() == BLOCK_TYPE_BLANK)
			{
				x = i * m_iBlockWidth + m_MapRect.left;
				y = j * m_iBlockHeight + m_MapRect.top;
				Tank p;
				p.init(x, y, m_MapRect);
				p.setTeam(TEAM_ENEMY);
				//p.setState(MOVE_STATE_DOWN);
				p.setAutoMode(true);
				// 세마리째 부터는 추적모드 on
				if (m_iEnemyCreaetedCount > 2)
				{
					p.setHoming(true);
				}	
				m_EnemyTanks.add(p);
				m_iEnemyCreaetedCount++;
				break;
			}
		}
	}

}

void GameManager::generateItem()
{
	int i, j, x, y;
	while (true)
	{
		i = rand() % m_iRowCount;
		j = rand() % m_iColCount;
		if (m_Map[i][j]->getData() == BLOCK_TYPE_BLANK)
		{
			x = i * m_iBlockWidth + m_MapRect.left;
			y = j * m_iBlockHeight + m_MapRect.top;

			m_item.init(x, y, m_MapRect);
			break;
		}
	}
}

bool GameManager::isValidRange(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= m_iRowCount) return false;
	if (y >= m_iColCount) return false;
	return true;
}
