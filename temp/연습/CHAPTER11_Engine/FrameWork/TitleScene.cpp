#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"

TitleScene::TitleScene()
{
	m_PlayerID = PLAYER_ID_BLACK;
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBlock = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//block00.bmp");
	m_iBlockWidth = m_pBlock->GetWidth();
	m_iBlockHeight = m_pBlock->GetHeight();

	m_pStone[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_black.bmp");	
	m_pStone[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_white.bmp");
	
	m_boardRect.Set(0, 0, m_iBlockWidth * BOARD_WIDTH, m_iBlockHeight * BOARD_HEIGHT);

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(m_aBoard[i], -1, sizeof(int) * BOARD_HEIGHT);
	}
		
	ZeroMemory(&m_iMousePos, sizeof(m_iMousePos));

	//JEngine::UIManager::GetInstance()->AddButton(10, 20, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
	//m_pTitle->SetAnchor(JEngine::ANCHOR_CENTER);
}

bool TitleScene::Input(float fETime)
{
	// ���� ���콺 ��ġ������ �޴´�.
	m_iMousePos = JEngine::InputManager::GetInstance()->GetMousePoint();

	// ���콺 Ŭ���� �� ����
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
	{
		if (m_boardRect.isPtin(m_iMousePos))
		{
			int x = m_iMousePos.x / m_iBlockWidth;
			int y = m_iMousePos.y / m_iBlockHeight;
			m_aBoard[x][y] = 0;
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
	// �������� �׸���.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			m_pBlock->DrawBitblt(i * m_iBlockWidth, j * m_iBlockHeight);			
		}
	}	
	
	// ������ ��ġ�� ������ �ٵϵ��� �׸���.
	m_pStone[0]->Draw((m_iMousePos.x / m_iBlockWidth) * m_iBlockWidth, (m_iMousePos.y / m_iBlockHeight) * m_iBlockHeight);

	// �̹� ������ ���� �׸���.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			if (m_aBoard[i][j] == 0 || m_aBoard[i][j] == 1)
			{
				m_pStone[m_aBoard[i][j]]->Draw(i * m_iBlockWidth, j * m_iBlockHeight);
			}			
		}
	}

}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	return true;
}