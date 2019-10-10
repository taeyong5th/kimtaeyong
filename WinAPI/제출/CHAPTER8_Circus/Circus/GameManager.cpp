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

	camera_x = 0;
	m_bg.init(camera_x, 0);
	m_Player.init(140, 430);
	m_jar.init(900, 0);
}

void GameManager::update()
{	
	static int player_x = 0;
	m_bg.update(camera_x, 0);
	m_bg.draw();
	
	m_jar.update(900 - camera_x, 445);
	m_jar.draw();

	static Goal goal;
	//goal.update(1600 - camera_x, 445);
	goal.update(700 - camera_x, 445);
	goal.draw();

	static FireCircle f;
	f.update(camera_x);
	f.draw(FIRE_L);
	m_Player.update(140 + player_x, 430);
	m_Player.draw();
	f.draw(FIRE_R);

	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);
	ReleaseDC(m_hWnd, hdc);

	// 마지막 지점 도달했는지 검사
	RECT rect;
	if (IntersectRect(&rect, &goal.getRect(), &m_Player.getRect()))
	{
		m_Player.setState(PLAYER_STATE_WIN);	
	}

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

GameManager::GameManager()
{	
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}

