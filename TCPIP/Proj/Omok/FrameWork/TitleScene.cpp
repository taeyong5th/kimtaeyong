#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{

}

void TitleScene::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	//JEngine::UIManager::GetInstance()->AddLabel("sdsdsdsds", 0, 0, 0);
	//JEngine::UIManager::GetInstance()->AddButton(200, 200, "res//stone_black.bmp", std::bind(&TitleScene::OnClick, this));

	m_pBlock = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//block00.bmp");
	m_iBlockWidth = m_pBlock->GetWidth();
	m_iBlockHeight = m_pBlock->GetHeight();

	m_pStone[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_black.bmp");	
	m_pStone[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_white.bmp");
	
	m_boardRect.Set(0, 0, m_iBlockWidth * BOARD_WIDTH, m_iBlockHeight * BOARD_HEIGHT);

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(m_aBoard[i], PLAYER_ID_NONE, sizeof(int) * BOARD_HEIGHT);
	}
		
	ZeroMemory(&m_iMousePos, sizeof(m_iMousePos));

	// 현재 플레이어의 돌 색깔
	m_PlayerID = PLAYER_ID_BLACK;

	//JEngine::UIManager::GetInstance()->AddButton(10, 20, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
	//m_pTitle->SetAnchor(JEngine::ANCHOR_CENTER);
}

bool TitleScene::Input(float fETime)
{
	// 현재 마우스 위치정보를 받는다.
	m_iMousePos = JEngine::InputManager::GetInstance()->GetMousePoint();

	// 마우스 클릭시 돌 놓기
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		if (m_boardRect.isPtin(m_iMousePos))
		{
			int x = m_iMousePos.x / m_iBlockWidth;
			int y = m_iMousePos.y / m_iBlockHeight;
			// 비어있는 공간이면 돌 놓음
			if (m_aBoard[x][y] == PLAYER_ID_NONE)
			{
				m_aBoard[x][y] = m_PlayerID;
			}
		}

		//JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		return true;
	}
		
	return false;
}

void TitleScene::Update(float fETime)
{
	
}

void TitleScene::Draw(HDC hdc)
{
	// 오목판을 그린다.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			m_pBlock->DrawBitblt(i * m_iBlockWidth, j * m_iBlockHeight);			
		}
	}
	
	// 놓여질 위치에 가상의 바둑돌을 그린다.
	if (m_PlayerID == PLAYER_ID_BLACK || m_PlayerID == PLAYER_ID_WHITE)
	{
		m_pStone[m_PlayerID]->Draw((m_iMousePos.x / m_iBlockWidth) * m_iBlockWidth, (m_iMousePos.y / m_iBlockHeight) * m_iBlockHeight);
	}

	// 이미 놓여진 돌을 전부 그린다.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			// 검은색 또는 흰색돌을 그림
			if (m_aBoard[i][j] == PLAYER_ID_BLACK || m_aBoard[i][j] == PLAYER_ID_WHITE)
			{
				m_pStone[m_aBoard[i][j]]->Draw(i * m_iBlockWidth, j * m_iBlockHeight);
			}			
		}
	}

}

void TitleScene::Release()
{

}


void TitleScene::showMessage(string caption, string text)
{
	MessageBox(m_hWnd, TEXT("Message TEXT"), TEXT("caption"), MB_OK);
}

bool TitleScene::OnClick()
{
	//JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	MessageBox(m_hWnd, TEXT("Message TEXT"), TEXT("caption"), MB_OK);

	return true;
}