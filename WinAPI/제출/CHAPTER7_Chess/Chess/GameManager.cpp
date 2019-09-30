#include "GameManager.h"

void GameManager::init()
{
	m_eTurn = TEAM_BLACK;
	m_SelectedPiece = nullptr;
	m_eState = STATE_PLAY;
	m_iTurnCount = 0;

	// ���� �� ����
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_BLACK_PAWN, (BOARD_POSITION_X)x, POS_7, TEAM_BLACK), (BOARD_POSITION_X)x, POS_7);
	}
	// ���� ����Ʈ ����
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_B, POS_8, TEAM_BLACK), POS_B, POS_8);
	m_board.setPiece(new Knight(IMG_BLACK_KNIGHT, POS_G, POS_8, TEAM_BLACK), POS_G, POS_8);
	// ���� �� ����
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_A, POS_8, TEAM_BLACK), POS_A, POS_8);
	m_board.setPiece(new Rook(IMG_BLACK_ROOK, POS_H, POS_8, TEAM_BLACK), POS_H, POS_8);
	// ���� ��� ����
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_C, POS_8, TEAM_BLACK), POS_C, POS_8);
	m_board.setPiece(new Bishop(IMG_BLACK_BISHOP, POS_F, POS_8, TEAM_BLACK), POS_F, POS_8);
	// ���� ��
	m_board.setPiece(new Queen(IMG_BLACK_QUEEN, POS_D, POS_8, TEAM_BLACK), POS_D, POS_8);
	// ���� ŷ
	m_board.setPiece(new King(IMG_BLACK_KING, POS_E, POS_8, TEAM_BLACK), POS_E, POS_8);
	
	
	// ���� �� ����
	for (UINT x = POS_A; x < POS_X_COUNT; x++)
	{
		m_board.setPiece(new Pawn(IMG_WHITE_PAWN, (BOARD_POSITION_X)x, POS_2, TEAM_WHITE), (BOARD_POSITION_X)x, POS_2);
	}
	// ���� ����Ʈ ����
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_B, POS_1, TEAM_WHITE), POS_B, POS_1);
	m_board.setPiece(new Knight(IMG_WHITE_KNIGHT, POS_G, POS_1, TEAM_WHITE), POS_G, POS_1);
	// ���� �� ����
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_A, POS_1, TEAM_WHITE), POS_A, POS_1);
	m_board.setPiece(new Rook(IMG_WHITE_ROOK, POS_H, POS_1, TEAM_WHITE), POS_H, POS_1);
	// ���� ��� ����
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_C, POS_1, TEAM_WHITE), POS_C, POS_1);
	m_board.setPiece(new Bishop(IMG_WHITE_BISHOP, POS_F, POS_1, TEAM_WHITE), POS_F, POS_1);
	// ���� �� ����
	m_board.setPiece(new Queen(IMG_WHITE_QUEEN, POS_D, POS_1, TEAM_WHITE), POS_D, POS_1);
	// ���� ŷ ����
	m_board.setPiece(new King(IMG_WHITE_KING, POS_E, POS_1, TEAM_WHITE), POS_E, POS_1);

}

void GameManager::start()
{
}

void GameManager::clickEvent(HWND hWnd, POINT point)
{
	if (m_eState == STATE_PLAY)
	{ // ������ ������ �ǽ��� ������ �ǽ� ����
		if (m_SelectedPiece == nullptr)
		{
			m_SelectedPiece = m_board.getPiece(point);			
		}
		// ������ �ǽ� �̵�
		else
		{
			std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> pos = m_board.calcPosition(point);
			std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> pos_list = m_SelectedPiece->getMovablePositions(&m_board);

			for (auto iter = pos_list.begin(); iter != pos_list.end(); ++iter)
			{
				if ((*iter) == pos)
				{
					// �̵��� �ڸ��� ���� �ִ� �ǽ��� ����
					Piece* p = m_SelectedPiece->move(&m_board, pos.first, pos.second);
					if (p != nullptr)
					{
						delete p;
					}
				}
			}

			// ���� ���� ������ ���� ���θ��
			Pawn* p = dynamic_cast<Pawn*>(m_SelectedPiece);
			if (p != nullptr)
			{
				if ((m_SelectedPiece->getTeam() == TEAM_BLACK && m_SelectedPiece->getPosition().second == POS_1)
					|| (m_SelectedPiece->getTeam() == TEAM_WHITE && m_SelectedPiece->getPosition().second == POS_8))
				{
					m_eState = STATE_PROMOTION;
				}
			}
			
			if (m_eState != STATE_PROMOTION)
			{
				m_SelectedPiece = nullptr;
				m_eTurn = (TEAM)(((int)m_eTurn + 1) % TEAM_COUNT);
				m_iTurnCount++;
			}
		}

		// �̵� �� ŷ�� üũ���ϴ��� Ȯ��
		if (isChecked(TEAM_BLACK))
		{
			MessageBox(hWnd, L"üũ", L"üũ��", MB_OK);
		}
	}
	// ���θ��
	else if (m_eState == STATE_PROMOTION)
	{
		PROMOTION_BUTTON btn = m_PromotionUI.click(point);
		BOARD_POSITION_X x = m_SelectedPiece->getPosition().first;
		BOARD_POSITION_Y y = m_SelectedPiece->getPosition().second;
		TEAM team = m_SelectedPiece->getTeam();
		Piece* piece;
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
			delete m_SelectedPiece;
			m_SelectedPiece = nullptr;
			m_eState = STATE_PLAY;
			break;
		case BUTTON_ROOK:
			if (team == TEAM_BLACK)
				piece = new Rook(IMG_BLACK_ROOK, x, y, team);
			else
				piece = new Rook(IMG_WHITE_ROOK, x, y, team);
			m_board.setPiece(piece, x, y);
			delete m_SelectedPiece;
			m_SelectedPiece = nullptr;
			m_eState = STATE_PLAY;
			break;
		case BUTTON_BISHOP:
			if (team == TEAM_BLACK)
				piece = new Bishop(IMG_BLACK_BISHOP, x, y, team);
			else
				piece = new Bishop(IMG_WHITE_BISHOP, x, y, team);
			m_board.setPiece(piece, x, y);
			delete m_SelectedPiece;
			m_SelectedPiece = nullptr;
			m_eState = STATE_PLAY;
			break;
		case BUTTON_KNIGHT:
			if (team == TEAM_BLACK)
				piece = new Knight(IMG_BLACK_KNIGHT, x, y, team);
			else
				piece = new Knight(IMG_WHITE_KNIGHT, x, y, team);
			m_board.setPiece(piece, x, y);
			delete m_SelectedPiece;
			m_SelectedPiece = nullptr;
			m_eState = STATE_PLAY;
			break;
		default:
			break;
		}
	}
	
	InvalidateRect(hWnd, NULL, TRUE);

}

void GameManager::draw(HDC hdc)
{
	// ���带 �׸���.
	m_board.draw(hdc);

	// ������ �׸���.
	m_GameInfoUI.draw(hdc, m_eTurn, m_iTurnCount);

	// ������ �ǽ��� �̵��� �� �ִ� ���� �׸���.
	if (m_SelectedPiece != nullptr)
	{
		m_SelectedPiece->drawMovablePositions(hdc, 0, 0, &m_board);
	}

	if (m_eState == STATE_PROMOTION)
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

			// ���� ���ݰ����� ��ġ�� ����Ѵ�.
			if (piece->getTeam() != team)
			{
				std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> positions;
				positions = piece->getAttackablePositions(&m_board);
				for (auto iter = positions.begin(); iter != positions.end(); ++iter)
				{
					s.insert(*iter);
				}
			}
			// �Ʊ� ŷ�� ������ ���Ѵ�.
			else
			{
				if (king == nullptr)
					king = dynamic_cast<King*>(piece);
			}
		}
	}

	for (auto iter = s.begin(); iter != s.end(); ++iter)
	{
		if (king != nullptr && king->getPosition() == *iter)
		{
			return true;
		}
	}
	return false;
}

GameManager::GameManager(HWND hWnd)
{
	// ��Ʈ�� �Ŵ����� �̹��� ���� �߰�
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
