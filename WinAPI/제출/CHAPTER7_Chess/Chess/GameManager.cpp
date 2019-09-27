#include "GameManager.h"

void GameManager::init()
{
	// ÈæÆÀ Æù ¼¼ÆÃ
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_BLACK_PAWN, (BOARD_POSITION_X)x, POS_7, TEAM_BLACK), (BOARD_POSITION_X)x, POS_7);
	}
	// ÈæÆÀ ³ªÀÌÆ® ¼¼ÆÃ
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_B, POS_8, TEAM_BLACK), POS_B, POS_8);
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_G, POS_8, TEAM_BLACK), POS_G, POS_8);
	// ÈæÆÀ ·è ¼¼ÆÃ
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_A, POS_8, TEAM_BLACK), POS_A, POS_8);
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_H, POS_8, TEAM_BLACK), POS_H, POS_8);
	// ÈæÆÀ ºñ¼ó ¼¼ÆÃ
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_C, POS_8, TEAM_BLACK), POS_C, POS_8);
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_F, POS_8, TEAM_BLACK), POS_F, POS_8);
	// ÈæÆÀ Äý
	m_board.setPiece(new Queen(IMG_BLACK_QUEEN, POS_D, POS_8, TEAM_BLACK), POS_D, POS_8);
	// ÈæÆÀ Å·
	m_board.setPiece(new King(IMG_BLACK_KING, POS_E, POS_8, TEAM_BLACK), POS_E, POS_8);
	
	
	// ¹éÆÀ Æù ¼¼ÆÃ
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_WHITE_PAWN, (BOARD_POSITION_X)x, POS_2, TEAM_WHITE), (BOARD_POSITION_X)x, POS_2);
	}
	// ¹éÆÀ ³ªÀÌÆ® ¼¼ÆÃ
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_B, POS_1, TEAM_WHITE), POS_B, POS_1);
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_G, POS_1, TEAM_WHITE), POS_G, POS_1);
	// ¹éÆÀ ·è ¼¼ÆÃ
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_A, POS_1, TEAM_WHITE), POS_A, POS_1);
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_H, POS_1, TEAM_WHITE), POS_H, POS_1);
	// ¹éÆÀ ºñ¼ó ¼¼ÆÃ
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_C, POS_1, TEAM_WHITE), POS_C, POS_1);
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_F, POS_1, TEAM_WHITE), POS_F, POS_1);
	// ¹éÆÀ Äý ¼¼ÆÃ
	m_board.setPiece(new Queen(IMG_WHITE_QUEEN, POS_D, POS_1, TEAM_WHITE), POS_D, POS_1);
	// ¹éÆÀ Å· ¼¼ÆÃ
	m_board.setPiece(new King(IMG_WHITE_KING, POS_E, POS_1, TEAM_WHITE), POS_E, POS_1);

}

void GameManager::start()
{
}

void GameManager::clickEvent(HWND hWnd, POINT point)
{
	// ÀÌÀü¿¡ ¼±ÅÃÇÑ ÇÇ½º°¡ ¾øÀ¸¸é ÇÇ½º ¼±ÅÃ
	if (m_SelectedPiece == nullptr)
	{
		m_SelectedPiece = m_board.getPiece(point);
	}
	// ÀÖÀ¸¸é ÇÇ½º ÀÌµ¿
	else
	{
		std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> pos = m_board.calcPosition(point);
		std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> pos_list = m_SelectedPiece->getMovablePositions(&m_board);

		for (auto iter = pos_list.begin(); iter != pos_list.end(); ++iter)
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
	//	MessageBox(hWnd, text, L"ÁÂÇ¥", MB_OK);*/
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
	// º¸µå¸¦ ±×¸°´Ù.
	m_board.draw(hdc, 0, 0);

	// ÇÇ½º¸¦ ±×¸°´Ù.
	if (m_SelectedPiece != nullptr)
	{
		m_SelectedPiece->drawMovablePositions(hdc, 0, 0, &m_board);
	}
}

GameManager::GameManager(HWND hWnd)
{
	// ºñÆ®¸Ê ¸Å´ÏÀú¿¡ ÀÌ¹ÌÁö Á¤º¸ Ãß°¡
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
