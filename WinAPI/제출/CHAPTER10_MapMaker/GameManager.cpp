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
	init();
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
	BitmapManager::GetInstance()->init(hdc, 580, 460);
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
	
	m_iBlockWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth();
	m_iBlockHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight();

	ReleaseDC(hWnd, hdc);
}

void GameManager::load()
{
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("stage.txt");
	TCHAR lpstrPath[MAX_PATH] = TEXT("");

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = TEXT("Text File\0*.txt\0Every File(*.*)\0*.*\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	GetCurrentDirectory(MAX_PATH, lpstrPath);
	OFN.lpstrInitialDir = lpstrPath;
	if (GetOpenFileName(&OFN) == 0)
	{
		DWORD err = CommDlgExtendedError();
		return;
	}

	// 불러오기에 성공하면 초기화
	init();
	HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
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

void GameManager::save()
{
	OPENFILENAME OFN;
	TCHAR str[300];
	TCHAR lpstrFile[MAX_PATH] = TEXT("stage.txt");
	TCHAR lpstrPath[MAX_PATH] = TEXT("");

	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = m_hWnd;
	OFN.lpstrFilter = TEXT("Text File\0*.txt\0Every File(*.*)\0*.*\0");
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	GetCurrentDirectory(MAX_PATH, lpstrPath);
	OFN.lpstrInitialDir = lpstrPath;
	if (GetSaveFileName(&OFN) == 0)
	{
		DWORD err = CommDlgExtendedError();
		return;
	}

	HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			DWORD writeB;
			TCHAR data = (char)(m_Map[i][j]->getData()) + 'A';
			WriteFile(hFile, &data, sizeof(TCHAR), &writeB, NULL);
		}
	}
	CloseHandle(hFile);
}

void GameManager::start()
{	
	// 게임시간 계산
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	if (m_bClickable == false)
	{
		m_fClickTime += m_fDeltaTime;
	}
	if (m_fClickTime > 0.2f)
	{
		m_fClickTime = 0.0f;
		m_bClickable = true;
	}

	//클릭
	POINT pt;
	int x = -1, y = -1;
	//마우스 포인트의 좌표를 가져온다.
	GetCursorPos(&pt);
	ScreenToClient(m_hWnd, &pt);
	
	if ((pt.x > m_iLeft) && (pt.y > m_iTop))
	{
		x = (pt.x - m_iLeft) / m_iBlockWidth;
		y = (pt.y - m_iTop) / m_iBlockHeight;
	}

	// x, y가 지뢰찾기 배열의 범위안이면
	if (isValidRange(x, y) && m_bClickable)
	{		
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			m_Map[x][y]->toggleNext();
			m_bClickable = false;
			// 텍스트 출력
			static TCHAR tempstr[128];
			static TCHAR tempstr2[128];
			wsprintf(tempstr, TEXT("%d"), x);
			wsprintf(tempstr2, TEXT("%d"), y);
			//MessageBox(m_hWnd, tempstr, tempstr2, MB_OK);

		}		
	}

	float bgRate[4] = {0.0f, 0.4f, 0.6f, 1.0f};
	
	// 배경 그리기
	int bgWidth = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getWidth(); // 실제 비트맵 이미지 가로
	int bgHeight = BitmapManager::GetInstance()->getBitmap(IMG_BG)->getHeight(); // 실제 비트맵 이미지 세로
	int blockWidth = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getWidth(); // 블럭한개 비트맵 가로
	int blockHeight = BitmapManager::GetInstance()->getBitmap(IMG_BLOCK_BLANK)->getHeight(); // 블럭한개  비트맵 세로
	int bgRealWidth = blockWidth * m_iRowCount + 90; // 배경이 실제 화면에 그려질 크기
	int bgRealHeight = blockHeight * m_iColCount + 90;

	// 상단 부분 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, 0, 1.0f, 1.0f, bgRate[0], bgRate[0], bgRate[1], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1], 0, (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])), 1.0f, bgRate[1], bgRate[0], bgRate[2], bgRate[1]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), 0, 1.0f, 1.0f, bgRate[2], bgRate[0], bgRate[3], bgRate[1]);

	// 중앙 부분	
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, bgHeight * bgRate[1], 1.0f, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])), bgRate[0], bgRate[1], bgRate[1], bgRate[2]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), bgHeight * bgRate[1], 1.0f, (bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]) - bgHeight * bgRate[1]) / (bgHeight * (bgRate[2] - bgRate[1])), bgRate[2], bgRate[1], bgRate[3], bgRate[2]);

	// 하단 부분 
	BitmapManager::GetInstance()->prepare(IMG_BG, 0, bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), 1.0f, 1.0f, bgRate[0], bgRate[2], bgRate[1], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgWidth * bgRate[1], bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), (bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]) - bgWidth * bgRate[1]) / (bgWidth * (bgRate[2] - bgRate[1])), 1.0f, bgRate[1], bgRate[2], bgRate[2], bgRate[3]);
	BitmapManager::GetInstance()->prepare(IMG_BG, bgRealWidth - bgWidth * (bgRate[3] - bgRate[2]), bgRealHeight - bgHeight * (bgRate[3] - bgRate[2]), 1.0f, 1.0f, bgRate[2], bgRate[2], bgRate[3], bgRate[3]);

	// 맵 그리기
	for (int i = 0; i < m_iRowCount; i++)
	{
		for (int j = 0; j < m_iColCount; j++)
		{
			m_Map[i][j]->draw(m_iLeft, m_iTop);
		}
	}

	// 실제 화면에 그린다.
	HDC hdc = GetDC(m_hWnd);
	BitmapManager::GetInstance()->draw(hdc, 0, 0);	
	ReleaseDC(m_hWnd, hdc);
}

void GameManager::init()
{
	m_iRowCount = MAP_WIDTH_MIN;
	m_iColCount = MAP_HEIGHT_MIN;

	// 지뢰 맵 초기화
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

	m_dwPrevTime = GetTickCount();
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = 0.0f;
	m_fClickTime = 0.0f;
	m_bClickable = true;
}


bool GameManager::isValidRange(int x, int y)
{
	if (x < 0) return false;
	if (y < 0) return false;
	if (x >= m_iRowCount) return false;
	if (y >= m_iColCount) return false;
	return true;
}
