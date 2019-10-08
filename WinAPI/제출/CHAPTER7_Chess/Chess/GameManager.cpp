#include "GameManager.h"

void GameManager::init()
{
	m_eTurn = TEAM_BLACK;
	m_SelectedPiece = nullptr;
	m_eState = STATE_CHOOSE_PIECE;
	m_iTurnCount = 0;

	m_board.clear();
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

void GameManager::clickEvent(HWND hWnd, POINT point)
{
	// �ǽ��� �ϳ� �����Ѵ�.
	if (m_eState == STATE_CHOOSE_PIECE)
	{
		m_SelectedPiece = m_board.getPiece(point);
		/*if (m_SelectedPiece != nullptr)
		{
			m_eState = STATE_CHOOSE_MOVE_POSITION;
		}*/
		if (m_SelectedPiece != nullptr && m_SelectedPiece->getTeam() == m_eTurn)
		{
			m_eState = STATE_CHOOSE_POSITION;
		}
		else if (m_SelectedPiece != nullptr && m_SelectedPiece->getTeam() != m_eTurn)
		{
			m_SelectedPiece = nullptr;
		}
	}
	// �ǽ��� �̵��Ѵ�.
	else if (m_eState == STATE_CHOOSE_POSITION)
	{
		std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> pos = m_board.calcPosition(point);
		std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> pos_list = m_SelectedPiece->getMovablePositions(&m_board);
		bool movable = false;

		// ���콺 Ŭ���� ��ġ�� �̵� �������� �˻�
		for (auto iter = pos_list.begin(); iter != pos_list.end(); ++iter)
		{
			if ((*iter) == pos)
			{
				movable = true;
				break;
			}
		}

		// �̵� �����ϸ� ������ �ǽ��� �̵�
		if (movable)
		{
			// �ǽ��� �̵� �� �� �ڸ��� �ִ� �ǽ��� ����
			Piece* p = m_SelectedPiece->move(&m_board, pos.first, pos.second);
			if (p != nullptr)
			{
				delete p;
			}
			// ���� ���� ������ ���� ���θ��
			Pawn* pawn = dynamic_cast<Pawn*>(m_SelectedPiece);
			if (pawn != nullptr)
			{
				if ((m_SelectedPiece->getTeam() == TEAM_BLACK && m_SelectedPiece->getPosition().second == POS_1)
					|| (m_SelectedPiece->getTeam() == TEAM_WHITE && m_SelectedPiece->getPosition().second == POS_8))
				{
					m_eState = STATE_CHOOSE_PROMOTION;
					InvalidateRect(hWnd, NULL, false);
					return;
				}
			}

			nextTurn();

			// üũ����Ʈ �˻�
			if (m_board.getMovablePositions(m_eTurn).size() == 0)
			{
				MessageBox(hWnd, L"üũ����Ʈ!", L"üũ����Ʈ!", MB_OK);
				init();
			}
			// �̵� �� ŷ�� üũ���ϴ��� Ȯ��
			else if (m_board.isChecked(m_eTurn))
			{
				MessageBox(hWnd, L"üũ!", L"üũ!", MB_OK);
			}
			// 50���̸� ���º�
			else if (m_iTurnCount > 50)
			{
				MessageBox(hWnd, L"���º�!", L"���º�!", MB_OK);
				init();
			}
			
		}
		// �̵��� �Ұ����ϸ� �ٽ� �ǽ��� ����
		else
		{
			m_SelectedPiece = nullptr;
			m_eState = STATE_CHOOSE_PIECE;
		}
	}
	// ���� ���θ���� �ǽ��� �����Ѵ�.
	else if (m_eState == STATE_CHOOSE_PROMOTION)
	{
		PROMOTION_BUTTON btn = m_PromotionUI.click(point);
		Piece* p = PromotePiece(m_SelectedPiece, btn);
		if (p != nullptr)
		{
			nextTurn();
			// üũ����Ʈ �˻�
			if (m_board.getMovablePositions(m_eTurn).size() == 0)
			{
				MessageBox(hWnd, L"üũ����Ʈ!", L"üũ����Ʈ!", MB_OK);
				init();
			}
			// �̵� �� ŷ�� üũ���ϴ��� Ȯ��
			else if (m_board.isChecked(m_eTurn))
			{
				MessageBox(hWnd, L"üũ!", L"üũ!", MB_OK);
			}
			// 50���̸� ���º�
			else if (m_iTurnCount > 50)
			{
				MessageBox(hWnd, L"���º�!", L"���º�!", MB_OK);
				init();
			}
		}
	}
	
	// ���� ��ư �������� �����
	if (m_GameInfoUI.click(point) == GAMEINFO_BUTTON_RESET)
	{
		init();
	}

	InvalidateRect(hWnd, NULL, false);
}

void GameManager::draw(HDC hdc)
{
	// ���带 �׸���.
	m_board.draw(hdc);

	// UI�� �׸���.
	m_GameInfoUI.update(m_eTurn, m_iTurnCount);
	m_GameInfoUI.draw(hdc);

	// ������ �ǽ��� �̵��� �� �ִ� ���� �׸���.
	if (m_SelectedPiece != nullptr)
	{
		m_SelectedPiece->drawMovablePositions(hdc, 0, 0, &m_board);
	}

	if (m_eState == STATE_CHOOSE_PROMOTION)
	{
		m_PromotionUI.draw(hdc);
	}
	BitmapManager::GetInstance()->draw(hdc, 0, 0, 500, 500);
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
	
}

GameManager::~GameManager()
{
	BitmapManager::GetInstance()->DestroyInstance();
}
