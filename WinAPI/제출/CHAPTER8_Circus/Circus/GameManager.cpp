#include "GameManager.h"

void GameManager::updateObjects(std::vector<CircusObject*> objects)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		(*iter)->update(camera_x);
	}
}

void GameManager::drawObjects(std::vector<CircusObject*> objects)
{
	for (auto iter = objects.begin(); iter != objects.end(); ++iter)
	{
		(*iter)->draw();
	}
}

void GameManager::intro()
{
	static bool isDraw = false;

	LPCWSTR stars[3];
	stars[0] = IMG_STAR1;
	stars[1] = IMG_STAR2;
	stars[2] = IMG_STAR3;

	int starCount = 0;
	int width = BitmapManager::GetInstance()->getBitmap(stars[0])->getWidth();
	while (starCount < 30)
	{
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], (WINDOW_WIDTH / 2 - width * 30) + width * 2.0f * starCount, 100, 2.0f, 2.0f);
		++starCount;
	}
	starCount = 0;
	while (starCount < 30)
	{
		BitmapManager::GetInstance()->prepare(stars[starCount % 3], (WINDOW_WIDTH / 2 - width * 30) + width * 2.0f * starCount, 400, 2.0f, 2.0f);
		++starCount;
	}

	int titleWidth = BitmapManager::GetInstance()->getBitmap(IMG_TITLE)->getWidth();
	int titleHeight = BitmapManager::GetInstance()->getBitmap(IMG_TITLE)->getHeight();
	BitmapManager::GetInstance()->prepare(IMG_TITLE, WINDOW_WIDTH / 2 -  titleWidth / 2, 150);

	if (!isDraw)
	{
		HDC hdc = GetDC(m_hWnd);
		BitmapManager::GetInstance()->draw(hdc, 0, 0);

		//RECT rt = { 100,100,400,300 };
		//DrawText(hdc, L"테스트123", -1, &rt, DT_CENTER | DT_WORDBREAK);
		
		// 텍스트 출력
		static TCHAR tempstr[128];
		wsprintf(tempstr, TEXT("PRESS ENTER"));
		TextOut(hdc, WINDOW_WIDTH / 2 - 60, 500, tempstr, lstrlen(tempstr));


		ReleaseDC(m_hWnd, hdc);
		isDraw = true;
	}
	

	if (GetKeyState(VK_RETURN) & 0x8000)
	{
		m_eState = GAME_PLAYING;
	}
}


void GameManager::update()
{
	switch (m_eState)
	{
	case GAME_INTRO:
		intro();
		break;
	case GAME_PLAYING:
		play();
		break;
	case GAME_OVER:
		m_dwCurTime = GetTickCount();
		m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
		m_dwPrevTime = m_dwCurTime;

		m_fPauseTime += m_fDeltaTime;
		if (m_fPauseTime > 3.0f)
		{
			init(m_hWnd);
			m_eState = GAME_PLAYING;
		}
		break;
	}
	
}

void GameManager::init(HWND hWnd)
{
	m_hWnd = hWnd;
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

	ReleaseDC(hWnd, hdc);

	player_x = 140;
	camera_x = 0;
	m_eState = GAME_INTRO;
	m_bg.init(camera_x, 0);
	m_Player.init(player_x, 430);


	m_jars[0].init(850, 445);
	m_jars[1].init(1850, 445);
	m_jars[2].init(2850, 445);

	m_goal.init(MAP_WIDTH, 445);
	m_fires[0].init(WINDOW_WIDTH, 270);
	m_fires[1].init(WINDOW_WIDTH + 500, 270);
	m_iHeart = 3;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fPauseTime = 0.0f;
}

void GameManager::play()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 플레이어가 마지막지점에 도착하면 승리
	if (m_Player.isCollision(&m_goal))
	{
		m_Player.setState(PLAYER_STATE_WIN);
		m_bg.setAnimState(BG_ANIM_TWINKLE);
		m_fires[0].setMovement(FIRE_STOP);
		m_fires[1].setMovement(FIRE_STOP);
		m_eState = GAME_OVER;
	}
	// 플레이어가 불덩이에 부딫히면 사망
	if (m_Player.isCollision(&m_fires[0]) || m_Player.isCollision(&m_fires[1]))
	{
		m_Player.setState(PLAYER_STATE_DIE);
		m_fires[0].setMovement(FIRE_STOP);
		m_fires[1].setMovement(FIRE_STOP);
		m_eState = GAME_OVER;
	}
	// 플레이어가 불주전자에 부딫히면 사망
	for (int i = 0; i < 3; ++i)
	{
		if (m_Player.isCollision(&m_jars[i]))
		{
			m_Player.setState(PLAYER_STATE_DIE);
			m_fires[0].setMovement(FIRE_STOP);
			m_fires[1].setMovement(FIRE_STOP);
			m_eState = GAME_OVER;
		}
	}


	// 각 오브젝트의 위치를 업데이트한다
	m_bg.update(camera_x);
	for (int i = 0; i < 3; ++i)
	{
		m_jars[i].update(camera_x);
	}
	m_goal.update(camera_x);
	m_fires[0].update(camera_x);
	m_fires[1].update(camera_x);
	m_Player.setPosition(player_x);
	m_Player.update(camera_x);


	// 메모리DC에 그린다.
	m_bg.draw();
	for (int i = 0; i < 3; ++i)
	{
		m_jars[i].draw();
	}
	m_goal.draw();
	m_fires[0].draw(FIRE_L); // 불덩이 왼쪽을 먼저 그린 후
	m_fires[1].draw(FIRE_L);
	m_Player.draw(); // 플레이어를 그리고
	m_fires[0].draw(FIRE_R); // 불덩이 오른쪽을 그린다.
	m_fires[1].draw(FIRE_R);

	// 실제 화면에 그린다.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	ReleaseDC(m_hWnd, hdc);

	// 게임을 멈추고 3초가 지나면 재시작
	if (m_eState == GAME_OVER)
	{
		
	}

	// 게임플레이중일때만 키입력을 받는다.
	if (m_eState == GAME_PLAYING)
	{
		// 카메라 위치가 끝에 닿으면 캐릭터를 움직인다.
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_Player.setState(PLAYER_STATE_MOVE);
			player_x -= PLAYER_SPEED * m_fDeltaTime;
			player_x = player_x < 140 ? 140 : player_x;
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			m_Player.setState(PLAYER_STATE_MOVE);
			player_x += PLAYER_SPEED * m_fDeltaTime;
			player_x = player_x > MAP_WIDTH ? MAP_WIDTH : player_x;
		}
		else
		{
			m_Player.setState(PLAYER_STATE_IDLE);
		}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			m_Player.setState(PLAYER_STATE_JUMP);
		}
	}

	camera_x = player_x - 140;
	if (camera_x > MAP_WIDTH - 800)
	{
		camera_x = MAP_WIDTH - 800;
	}
}

GameManager::GameManager()
{	
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}

