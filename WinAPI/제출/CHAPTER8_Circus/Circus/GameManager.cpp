#include "GameManager.h"

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

void GameManager::gameIntro()
{
	m_IntroUI.draw();

	// enter키를 누르면 플레이한다.
	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		m_iMapWidth = DEFAULT_MAP_WIDTH;
		gameInit();
		m_eState = GAME_PLAY;
		m_iScore = 0;
		m_iHeart = MAX_HEART;
	}
}

void GameManager::gameInit()
{
	const int y = 100;
	m_iPlayerX = 200;
	m_iCameraX = 0;
	m_eState = GAME_INTRO;
	m_bg.init(m_iCameraX, 0 + y);
	m_Player.init(m_iPlayerX, 430 + y);

	m_eJarCount = m_iMapWidth / 1000;
	if (m_jars != nullptr) delete[] m_jars;
	if (m_Meters != nullptr) delete[] m_Meters;
	m_jars = new Jar[m_eJarCount];
	m_Meters = new Meter[m_eJarCount];
	for (int i = 0; i < m_eJarCount; ++i)
	{
		m_jars[i].init(i * 1000 + 900, 445 + y);
		m_Meters[i].init(i * 1000 + 1000, 530 + y, m_iMapWidth);
	}

	m_goal.init(m_iMapWidth + 50, 445 + y);
	m_fires[0].init(WINDOW_WIDTH, 270 + y);
	m_fires[1].init(WINDOW_WIDTH + 500, 270 + y);

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fPauseTime = 0.0f;
}

void GameManager::gamePlay()
{
	// 플레이어가 마지막지점에 도착하면 승리
	if (m_Player.isCollision(&m_goal))
	{
		m_iScore += 1000;
		m_iBestScore = m_iScore > m_iBestScore ? m_iScore : m_iBestScore;
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
	for (int i = 0; i < m_eJarCount; ++i)
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
	for (int i = 0; i < m_eJarCount; ++i)
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
	if (m_iBestScore > loadScore())
	{
		saveScore(m_iBestScore);
	}

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
		m_iPlayerX = m_iPlayerX > m_iMapWidth ? m_iMapWidth : m_iPlayerX;
	}
	else
	{
		m_Player.setState(PLAYER_STATE_IDLE);
	}
	if (GetKeyState(VK_SPACE) & 0x8000 || GetKeyState(VK_UP) & 0x8000)
	{
		m_Player.setState(PLAYER_STATE_JUMP);
	}
	if (GetKeyState(VK_ESCAPE) & 0x8000)
	{
		m_eState = GAME_INTRO;
	}

	// 카메라 위치 보정
	m_iCameraX = m_iPlayerX - 140;
	if (m_iCameraX > m_iMapWidth - 800)
	{
		m_iCameraX = m_iMapWidth - 800;
	}
}

void GameManager::gameOver()
{
	// 캐릭터를 사망이미지로 바꾸고 불덩이를 멈춘다.
	m_Player.setState(PLAYER_STATE_DIE);
	m_fires[0].setMovement(FIRE_STOP);
	m_fires[1].setMovement(FIRE_STOP);
	for (int i = 0; i < m_eJarCount; ++i)
	{
		m_jars[i].setAnimation(JAR_ANIM_STOP);
	}

	draw();

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 게임을 멈추고 2초가 지나면 재시작
	m_fPauseTime += m_fDeltaTime;
	if (m_fPauseTime > 2.0f)
	{
		if (m_iHeart < 1)
		{
			m_eState = GAME_INTRO;
		}
		else
		{
			gameInit();
			m_eState = GAME_PLAY;
		}
	}
}

void GameManager::gameClear()
{
	// 캐릭터를 승리이미지로 바꾸고 관중을 반짝이게한다.
	m_Player.setState(PLAYER_STATE_WIN);
	m_bg.setAnimState(BG_ANIM_TWINKLE);
	m_fires[0].setMovement(FIRE_STOP);
	m_fires[1].setMovement(FIRE_STOP);
	for (int i = 0; i < m_eJarCount; ++i)
	{
		m_jars[i].setAnimation(JAR_ANIM_STOP);
	}

	draw();

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 게임을 멈추고 2초가 지나면 재시작
	m_fPauseTime += m_fDeltaTime;
	if (m_fPauseTime > 2.0f)
	{
		m_iMapWidth += 1000;
		gameInit();
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
	if (m_iCameraX > m_iMapWidth - 800)
	{
		m_iCameraX = m_iMapWidth - 800;
	}

}

void GameManager::draw()
{
	// 각 오브젝트의 위치를 업데이트한다
	m_bg.update(m_iCameraX);
	for (int i = 0; i < m_eJarCount; ++i)
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
	for (int i = 0; i < m_eJarCount; ++i)
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

int GameManager::loadScore()
{
	int score = 0;
	std::ifstream file;
	file.open(BEST_SCORE_FILEPATH, std::ios_base::in);
	
	if (file.is_open())
	{
		file >> score;		
	}
	file.close();
	
	return score;
}

bool GameManager::saveScore(int score)
{
	std::ofstream file;
	file.open(BEST_SCORE_FILEPATH, std::ios_base::out);
	// 파일 열기 실패
	if (!file.is_open()) return false;

	std::string str(std::to_string(score));
	file.write(str.c_str(), str.size());	
	file.close();
	return true;
}

void GameManager::initResource(HWND hWnd)
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
	BitmapManager::GetInstance()->add(new Bitmap(m_hWnd, IMG_ICON_BLANK));
	ReleaseDC(hWnd, hdc);
}

GameManager::GameManager()
{
	m_iScore = 0;
	m_iBestScore = loadScore();
	m_iHeart = MAX_HEART;
	m_iMapWidth = DEFAULT_MAP_WIDTH;
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
	if (m_jars != nullptr) delete[] m_jars;
	if (m_Meters != nullptr) delete[] m_Meters;
}

