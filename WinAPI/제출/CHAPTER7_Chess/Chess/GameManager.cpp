#include "GameManager.h"

void GameManager::init()
{
	// 흑팀 폰 세팅
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_BLACK_PAWN, (BOARD_POSITION_X)x, POS_7, TEAM_BLACK), (BOARD_POSITION_X)x, POS_7);
	}	
	
	// 백팀 폰 세팅
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_WHITE_PAWN, (BOARD_POSITION_X)x, POS_2, TEAM_WHITE), (BOARD_POSITION_X)x, POS_2);
	}
}

void GameManager::start()
{
}

void GameManager::clickEvent(HWND hWnd, POINT point)
{
	// 이전에 선택한 피스가 없으면 피스 선택
	if (m_SelectedPiece == nullptr)
	{
		m_SelectedPiece = m_board.getPiece(point);
	}
	// 있으면 피스 이동
	else
	{
		std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> pos = m_board.calcPosition(point);
		std::vector<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> vec = m_SelectedPiece->getMovablePositions(&m_board);

		for (auto iter = vec.begin(); iter != vec.end(); ++iter)
		{
			if ((*iter) == pos)
			{
				m_SelectedPiece->move(&m_board, pos.first, pos.second);
			}
		}
		m_SelectedPiece = nullptr;
	}
	
	//if (m_SelectedPiece != nullptr) 
	//{
	//	/*int x = m_SelectedPiece->getPosition().first;
	//	int y = m_SelectedPiece->getPosition().second;
	//	static TCHAR text[128];
	//	wsprintf(text, TEXT("[%d, %d]"),
	//		x, y);
	//	MessageBox(hWnd, text, L"좌표", MB_OK);*/
	//}

	InvalidateRect(hWnd, NULL, TRUE);

	//for (UINT i = POS_A; i < POS_X_COUNT; i++)
	//{
	//	for (UINT j = POS_8; j < POS_Y_COUNT; j++)
	//	{
	//		m_SelectedPiece = m_board.getPiece((BOARD_POSITION_X)i, (BOARD_POSITION_Y)j);
	//		//m_SelectedPiece->move(&m_board, POS_B, POS_4);
	//		if (m_SelectedPiece == nullptr) {
	//			exit(0);
	//		}
	//	}
	//}
}

void GameManager::draw(HDC hdc)
{
	// 보드를 그린다.
	m_board.draw(hdc, 0, 0);

	// 피스를 그린다.
	if (m_SelectedPiece != nullptr)
	{
		m_SelectedPiece->drawMovablePositions(hdc, 0, 0, &m_board);
	}
}

GameManager::GameManager(HWND hWnd)
{
	// 비트맵 매니저에 이미지 정보 추가
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_PAWN));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_KNIGHT));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_BISHOP));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_ROOK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_QUEEN));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BLACK_KING));

	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_PAWN));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_KNIGHT));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_BISHOP));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_ROOK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_QUEEN));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_WHITE_KING));

	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BOARD_WHITE));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BOARD_BLACK));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BOARD_SELECTED));
	BitmapManager::GetInstance()->add(new Bitmap(hWnd, IMG_BOARD_MOVABLE));

	m_SelectedPiece = nullptr;

	// https://locofield.com/1
	// https://en.cppreference.com/w/cpp/filesystem/is_directory
	// https://stackoverflow.com/questions/27720553/conversion-of-wchar-t-to-string
	//std::wstring imgPath(IMG_PATH);
	/*std::string dir(imgPath.begin(), imgPath.end());

	for (auto& p : std::experimental::filesystem::directory_iterator(dir))
	{
		if (!std::experimental::filesystem::is_directory(p.status()))
		{
			std::string str = p.path().string();
			std::wstring wstr(str.begin(), str.end());
			BitmapManager::GetInstance()->add(new Bitmap(hWnd, wstr.c_str()));
		}
	}*/
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}
