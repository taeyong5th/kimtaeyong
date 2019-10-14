#include "GameManager.h"

void GameManager::update()
{
	switch (m_eState)
	{
	case GAME_INTRO:
		intro();
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

void GameManager::intro()
{
	m_IntroUI.draw();

	// enter키를 누르면 플레이한다.
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		init(m_hWnd);
		m_eState = GAME_PLAY;
	}
}

void GameManager::gamePlay()
{
	// 플레이어가 마지막지점에 도착하면 승리
	if (m_Player.isCollision(&m_goal))
	{
		m_eState = GAME_CLEAR;
		return;
	}
	// 플레이어가 불덩이에 부딫히면 사망
	if (m_Player.isCollision(&m_fires[0]) || m_Player.isCollision(&m_fires[1]))
	{
		--m_iHeart;
		m_eState = GAME_OVER;
		return;
	}
	// 플레이어가 불주전자에 부딫히면 사망
	for (int i = 0; i < 3; ++i)
	{
		if (m_Player.isCollision(&m_jars[i]))
		{
			--m_iHeart;
			m_eState = GAME_OVER;
			return;
		}
	}

	// 점수획득
	for (int i = 0; i < 2; ++i)
	{
		if (m_Player.getX() > m_fires[i].getX())
		{
			if (!m_fires[i].isAcquired())
			{
				m_iScore += 100;
			}
			m_fires[i].setScoreAcquired(true);
		}
	}
	for (int i = 0; i < 3; ++i)
	{
		if (m_Player.getX() > m_jars[i].getX())
		{
			if (!m_jars[i].isAcquired())
			{
				m_iScore += 300;
			}
			m_jars[i].setScoreAcquired(true);
		}
	}
	m_iBestScore = m_iScore > m_iBestScore ? m_iScore : m_iBestScore;

	// 화면을 그린다.
	draw();


	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 키를 누르면 캐릭터를 움직인다.
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_Player.setState(PLAYER_STATE_MOVE);
		m_iPlayerX -= PLAYER_SPEED * m_fDeltaTime;
		m_iPlayerX = m_iPlayerX < 140 ? 140 : m_iPlayerX;
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_Player.setState(PLAYER_STATE_MOVE);
		m_iPlayerX += PLAYER_SPEED * m_fDeltaTime;
		m_iPlayerX = m_iPlayerX > MAP_WIDTH ? MAP_WIDTH : m_iPlayerX;
	}
	else
	{
		m_Player.setState(PLAYER_STATE_IDLE);
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_Player.setState(PLAYER_STATE_JUMP);
	}

	// 카메라 위치 보정
	m_iCameraX = m_iPlayerX - 140;
	if (m_iCameraX > MAP_WIDTH - 800)
	{
		m_iCameraX = MAP_WIDTH - 800;
	}
}

void GameManager::gameOver()
{
	// 캐릭터를 사망이미지로 바꾸고 불덩이를 멈춘다.
	m_Player.setState(PLAYER_STATE_DIE);
	m_fires[0].setMovement(FIRE_STOP);
	m_fires[1].setMovement(FIRE_STOP);
	draw();

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 게임을 멈추고 3초가 지나면 재시작
	m_fPauseTime += m_fDeltaTime;
	if (m_fPauseTime > 3.0f)
	{
		init(m_hWnd);
		m_eState = GAME_PLAY;
	}
}

void GameManager::gameClear()
{
	// 캐릭터를 승리이미지로 바꾸고 관중을 반짝이게한다.
	m_Player.setState(PLAYER_STATE_WIN);
	m_bg.setAnimState(BG_ANIM_TWINKLE);
	m_fires[0].setMovement(FIRE_STOP);
	m_fires[1].setMovement(FIRE_STOP);
	draw();

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 게임을 멈추고 3초가 지나면 재시작
	m_fPauseTime += m_fDeltaTime;
	if (m_fPauseTime > 3.0f)
	{
		init(m_hWnd);
		m_eState = GAME_PLAY;
	}

	// 캐릭터 골인지점 위치 보정
	if (m_Player.getX() < m_goal.getX() - 5)
	{
		m_iPlayerX += PLAYER_SPEED * m_fDeltaTime / 2;
	}
	else if (m_Player.getX() > m_goal.getX() + 5)
	{
		m_iPlayerX -= PLAYER_SPEED * m_fDeltaTime / 2;
	}
	// 카메라 위치 보정
	m_iCameraX = m_iPlayerX - 140;
	if (m_iCameraX > MAP_WIDTH - 800)
	{
		m_iCameraX = MAP_WIDTH - 800;
	}

}

void GameManager::draw()
{
	// 각 오브젝트의 위치를 업데이트한다
	m_bg.update(m_iCameraX);
	for (int i = 0; i < 3; ++i)
	{
		m_jars[i].update(m_iCameraX);
		m_Meters[i].update(m_iCameraX);
	}
	m_goal.update(m_iCameraX);
	m_fires[0].update(m_iCameraX);
	m_fires[1].update(m_iCameraX);
	m_Player.setPosition(m_iPlayerX);
	m_Player.update(m_iCameraX);

	// 메모리DC에 그린다.
	m_bg.draw();
	for (int i = 0; i < 3; ++i)
	{
		m_jars[i].draw();
		m_Meters[i].draw();
	}
	m_goal.draw();
	m_fires[0].draw(FIRE_L); // 불덩이 왼쪽을 먼저 그린 후
	m_fires[1].draw(FIRE_L);
	m_Player.draw(); // 플레이어를 그리고
	m_fires[0].draw(FIRE_R); // 불덩이 오른쪽을 그린다.
	m_fires[1].draw(FIRE_R);

	m_ScoreUI.draw(m_iScore, m_iBestScore, m_iHeart, 0, 0, 1.5f);

	// 실제 화면에 그린다.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::init(HWND hWnd)
{
	m_hWnd = hWnd;

	m_IntroUI.init(hWnd);

	HDC hdc = GetDC(hWnd);

	BitmapManager::GetInstance()->init(hdc, WINDOW_WIDTH, WINDOW_HEIGHT);
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//back.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//back_deco.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//back_normal.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//back_normal2.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//cash.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//die.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//end.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_1b.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_1f.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_b.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_f.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_l.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_l_b.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy_l_f.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//enemy1.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//front.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//front2.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//icon.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//miter.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//player0.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//player1.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//player2.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//star.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//star1.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//star2.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//win.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, L"res//win2.bmp"));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, IMG_NUMBER));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, IMG_TITLE));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, IMG_NOW));
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, IMG_BEST));

	ReleaseDC(hWnd, hdc);
	
	m_iScore = 0;

	int tempY = 100;
	m_iPlayerX = 200;
	m_iCameraX = 0;
	m_eState = GAME_INTRO;
	m_bg.init(m_iCameraX, 0 + tempY);
	m_Player.init(m_iPlayerX, 430 + tempY);


	for (int i = 0; i < 3; ++i)
	{
		m_jars[i].init(i * 1000 + 900, 445 + tempY);
		m_Meters[i].init(i * 1000 + 1000, 530 + tempY);
	}

	m_goal.init(MAP_WIDTH + 50 , 445 + tempY);
	m_fires[0].init(WINDOW_WIDTH, 270 + tempY);
	m_fires[1].init(WINDOW_WIDTH + 500, 270 + tempY);

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fPauseTime = 0.0f;
}

GameManager::GameManager()
{
	m_iBestScore = 0;
	m_iHeart = 3;
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}

