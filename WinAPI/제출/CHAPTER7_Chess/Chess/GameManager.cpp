#include "GameManager.h"

void GameManager::init()
{
	m_eTurn = TEAM_BLACK;
	m_SelectedPiece = nullptr;
	m_eState = STATE_CHOOSE_PIECE;
	m_iTurnCount = 0;

	// 흑팀 폰 세팅
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_BLACK_PAWN, (BOARD_POSITION_X)x, POS_7, TEAM_BLACK), (BOARD_POSITION_X)x, POS_7);
	}
	// 흑팀 나이트 세팅
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_B, POS_8, TEAM_BLACK), POS_B, POS_8);
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_G, POS_8, TEAM_BLACK), POS_G, POS_8);
	// 흑팀 룩 세팅
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_A, POS_8, TEAM_BLACK), POS_A, POS_8);
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_H, POS_8, TEAM_BLACK), POS_H, POS_8);
	// 흑팀 비숍 세팅
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_C, POS_8, TEAM_BLACK), POS_C, POS_8);
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_F, POS_8, TEAM_BLACK), POS_F, POS_8);
	// 흑팀 퀸
	m_board.setPiece(new Queen(IMG_BLACK_QUEEN, POS_D, POS_8, TEAM_BLACK), POS_D, POS_8);
	// 흑팀 킹
	m_blackKing = new King(IMG_BLACK_KING, POS_E, POS_8, TEAM_BLACK);
	m_board.setPiece(m_blackKing, POS_E, POS_8);
	
	
	// 백팀 폰 세팅
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_WHITE_PAWN, (BOARD_POSITION_X)x, POS_2, TEAM_WHITE), (BOARD_POSITION_X)x, POS_2);
	}
	// 백팀 나이트 세팅
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_B, POS_1, TEAM_WHITE), POS_B, POS_1);
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_G, POS_1, TEAM_WHITE), POS_G, POS_1);
	// 백팀 룩 세팅
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_A, POS_1, TEAM_WHITE), POS_A, POS_1);
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_H, POS_1, TEAM_WHITE), POS_H, POS_1);
	// 백팀 비숍 세팅
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_C, POS_1, TEAM_WHITE), POS_C, POS_1);
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_F, POS_1, TEAM_WHITE), POS_F, POS_1);
	// 백팀 퀸 세팅
	m_board.setPiece(new Queen(IMG_WHITE_QUEEN, POS_D, POS_1, TEAM_WHITE), POS_D, POS_1);
	// 백팀 킹 세팅
	m_whiteKing = new King(IMG_WHITE_KING, POS_E, POS_1, TEAM_WHITE);
	m_board.setPiece(m_whiteKing, POS_E, POS_1);
}

void GameManager::start()
{
}

void GameManager::clickEvent(HWND hWnd, POINT point)
{
	if (m_eState == STATE_CHOOSE_PIECE)
	{
		m_SelectedPiece = m_board.getPiece(point);
		/*if (m_SelectedPiece != nullptr)
		{
			m_eState = STATE_CHOOSE_MOVE_POSITION;
		}*/
		if (m_SelectedPiece != nullptr && m_SelectedPiece->getTeam() == m_eTurn)
		{
			m_eState = STATE_CHOOSE_MOVE_POSITION;
		}
		else if (m_SelectedPiece != nullptr && m_SelectedPiece->getTeam() != m_eTurn)
		{
			m_SelectedPiece = nullptr;
		}
	}
	else if (m_eState == STATE_CHOOSE_MOVE_POSITION)
	{
		std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> pos = m_board.calcPosition(point);
		std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> pos_list = m_SelectedPiece->getMovablePositions(&m_board);
		bool movable = false;

		// 마우스 클릭한 위치로 이동 가능한지 검사
		for (auto iter = pos_list.begin(); iter != pos_list.end(); ++iter)
		{
			if ((*iter) == pos)
			{
				movable = true;
				break;
			}
		}

		// 이동 가능하면 선택한 피스를 이동
		if (movable)
		{
			// 피스를 이동 후 그 자리에 있던 피스를 제거
			Piece* p = m_SelectedPiece->move(&m_board, pos.first, pos.second);
			if (p != nullptr)
			{
				delete p;
			}
			// 폰이 가장 끝으로 가면 프로모션
			Pawn* pawn = dynamic_cast<Pawn*>(m_SelectedPiece);
			if (pawn != nullptr)
			{
				if ((m_SelectedPiece->getTeam() == TEAM_BLACK && m_SelectedPiece->getPosition().second == POS_1)
					|| (m_SelectedPiece->getTeam() == TEAM_WHITE && m_SelectedPiece->getPosition().second == POS_8))
				{
					m_eState = STATE_CHOOSE_PROMOTION;
					InvalidateRect(hWnd, NULL, TRUE);
					return;
				}
			}

			// 이동 후 킹이 체크당하는지 확인
			if (isChecked(m_eTurn))
			{
				MessageBox(hWnd, L"체크", L"체크됨", MB_OK);
				isCheckMate();
			}
			nextTurn();
		}
		// 이동이 불가능하면 다시 피스를 선택
		else
		{
			m_SelectedPiece = nullptr;
			m_eState = STATE_CHOOSE_PIECE;
		}
	}
	// 프로모션 선택 화면
	else if (m_eState == STATE_CHOOSE_PROMOTION)
	{
		PROMOTION_BUTTON btn = m_PromotionUI.click(point);
		Piece* p = PromotePiece(m_SelectedPiece, btn);
		if (p != nullptr)
		{
			nextTurn();
		}
	}

	
	InvalidateRect(hWnd, NULL, TRUE);

}

void GameManager::draw(HDC hdc)
{
	// 보드를 그린다.
	m_board.draw(hdc);

	// 게임을 그린다.
	m_GameInfoUI.draw(hdc, m_eTurn, m_iTurnCount);

	// 선택한 피스가 이동할 수 있는 곳을 그린다.
	if (m_SelectedPiece != nullptr)
	{
		m_SelectedPiece->drawMovablePositions(hdc, 0, 0, &m_board);
	}

	if (m_eState == STATE_CHOOSE_PROMOTION)
	{
		m_PromotionUI.draw(hdc);
	}
}

bool GameManager::isChecked(TEAM team)
{
	Piece* piece;
	King* king = nullptr;
	std::set<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> s;

	for (UINT i = 0; i < BOARD_WIDTH; i++)
	{
		for (UINT j = 0; j < BOARD_HEIGHT; j++)
		{
			piece = m_board.getPiece((BOARD_POSITION_X)i, (BOARD_POSITION_Y)j);
			if (piece == nullptr) continue;

			// 적이 공격가능한 위치를 계산한다.
			if (piece->getTeam() == team)
			{
				std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> positions;
				positions = piece->getAttackablePositions(&m_board);
				for (auto iter = positions.begin(); iter != positions.end(); ++iter)
				{
					//s.insert(*iter);
				}
			}
			// 아군 킹의 정보를 구한다.
			else
			{
				if (king == nullptr)
					king = dynamic_cast<King*>(piece);
			}
		}
	}
	s = m_board.getAttackablePositions(team);

	for (auto iter = s.begin(); iter != s.end(); ++iter)
	{
		if (king != nullptr && king->getPosition() == *iter)
		{
			return true;
		}
	}
	return false;
}

bool GameManager::isCheckMate()
{
	if (m_whiteKing->getMovablePositions(&m_board).size() == 0)
	{
		//exit(0);
		// 킹이 체크되어 이동할수 있는 곳이 0일때
		// 킹을 체크 중인 적 피스를 다음턴에 잡을 수 없으면 체크메이트,
		// 아니면 그냥 체크.

	}

	return false;
}

Piece* GameManager::PromotePiece(Piece* pawn, PROMOTION_BUTTON btn)
{
	BOARD_POSITION_X x = pawn->getPosition().first;
	BOARD_POSITION_Y y = pawn->getPosition().second;
	TEAM team = pawn->getTeam();
	Piece* piece = nullptr;
	switch (btn)
	{
	case BUTTON_NONE:
		break;
	case BUTTON_QUEEN:
		if (team == TEAM_BLACK)
			piece = new Queen(IMG_BLACK_QUEEN, x, y, team);
		else
			piece = new Queen(IMG_WHITE_QUEEN, x, y, team);
		m_board.setPiece(piece, x, y);
		delete pawn;
		break;
	case BUTTON_ROOK:
		if (team == TEAM_BLACK)
			piece = new Rook(IMG_BLACK_ROOK, x, y, team);
		else
			piece = new Rook(IMG_WHITE_ROOK, x, y, team);
		m_board.setPiece(piece, x, y);
		delete pawn;
		break;
	case BUTTON_BISHOP:
		if (team == TEAM_BLACK)
			piece = new Bishop(IMG_BLACK_BISHOP, x, y, team);
		else
			piece = new Bishop(IMG_WHITE_BISHOP, x, y, team);
		m_board.setPiece(piece, x, y);
		delete pawn;
		break;
	case BUTTON_KNIGHT:
		if (team == TEAM_BLACK)
			piece = new Knight(IMG_BLACK_KNIGHT, x, y, team);
		else
			piece = new Knight(IMG_WHITE_KNIGHT, x, y, team);
		m_board.setPiece(piece, x, y);
		delete pawn;
		break;
	default:
		break;
	}

	return piece;
}

void GameManager::nextTurn()
{
	m_SelectedPiece = nullptr;
	m_eTurn = (TEAM)(((int)m_eTurn + 1) % TEAM_COUNT);
	m_iTurnCount++;
	m_eState = STATE_CHOOSE_PIECE;
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
