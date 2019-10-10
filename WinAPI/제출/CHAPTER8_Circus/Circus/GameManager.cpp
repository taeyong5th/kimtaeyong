#include "GameManager.h"

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

	ReleaseDC(hWnd, hdc);

	player_x = camera_x = 0;
	m_eState = GAME_PLAYING;
	m_bg.init(camera_x, 0);
	m_Player.init(140, 430);
	m_jar.init(900, 0);
	m_goal.init(900, 445);
	m_fire.init(600, 270);
	m_iHeart = 3;

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fPauseTime = 0.0f;
}

void GameManager::update()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	// 플레이어가 마지막지점에 도착하거나 죽으면 게임을 멈춘다
	RECT rect;
	if (IntersectRect(&rect, &m_goal.getRect(), &m_Player.getRect()))
	{
		m_Player.setState(PLAYER_STATE_WIN);
		m_eState = GAME_PAUSE;
	}
	if (   IntersectRect(&rect, &m_fire.getRect(), &m_Player.getRect())
		|| IntersectRect(&rect, &m_jar.getRect(), &m_Player.getRect()))
	{ 
		m_Player.setState(PLAYER_STATE_DIE);
		m_fire.setMovement(FIRE_STOP);
		m_eState = GAME_PAUSE;
	}

	m_bg.update(camera_x, 0);	
	m_jar.update(770 - camera_x, 445);
	m_goal.update(900 - camera_x, 445);

	m_bg.draw();
	m_jar.draw();
	m_goal.draw();

	m_fire.update(camera_x);
	m_fire.draw(FIRE_L);
	m_Player.update(140 + player_x);
	m_Player.draw();
	m_fire.draw(FIRE_R);

	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	ReleaseDC(m_hWnd, hdc);

	
	// 게임을 멈추고 3초가 지나면 재시작
	if (m_eState == GAME_PAUSE)
	{
		m_fPauseTime += m_fDeltaTime;
		if (m_fPauseTime > 3.0f)
		{
			init(m_hWnd);
		}
	}

	// 게임플레이중일때만 키입력을 받는다.
	if (m_eState == GAME_PLAYING)
	{
		// 카메라 위치가 끝에 닿으면 캐릭터를 움직인다.
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			m_Player.setState(PLAYER_STATE_MOVE);
			if (player_x <= 0)
			{
				camera_x -= GAME_SPEED;
				camera_x = camera_x < 0 ? 0 : camera_x;
			}
			else
			{
				player_x -= GAME_SPEED;
				player_x = player_x < 0 ? 0 : player_x;
			}
		}
		else if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			m_Player.setState(PLAYER_STATE_MOVE);
			if (camera_x == 800)
			{
				player_x += GAME_SPEED;
				player_x = player_x > 700 ? 700 : player_x;
			}
			else
			{
				camera_x += GAME_SPEED;
				camera_x = camera_x > 800 ? 800 : camera_x;
			}
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
	
}

GameManager::GameManager()
{	
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}

