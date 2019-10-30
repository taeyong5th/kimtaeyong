#include "AirplaneGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"


void AirplaneGameScene::Init(HWND hWnd)
{

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameBack.bmp");

	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//TimeOver.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect.bmp");
	m_pFeverBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FeverEffect3.bmp");
	m_pFeverBar1 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever1.bmp");
	m_pFeverBar2 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever2.bmp");
	m_pFeverBar3 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//Fever3.bmp");

	m_pFlight = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameFlight.bmp");
	m_pBullet = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameBullet.bmp");
	m_pStar1 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameStar1.bmp");
	m_pStar2 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameStar2.bmp");
	m_pStar3 = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameStar3.bmp");

	m_pTimeOver->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pFlight->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pBullet->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pStar1->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pStar2->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pStar3->SetAnchor(JEngine::ANCHOR_CENTER);
	
	m_iScore = 0;
	m_iFeverScore = 0;
	m_fPlayTime = 0.0f;
	m_fFeverTime = 0.0f;
	m_fGameOverTime = 0.0f;
	m_fFeverAnimTime = 0.0f;

	m_eState = GAME_STATE_PLAY;
	memset(&m_MousePos, 0, sizeof(m_MousePos));
	x = 208;
	y = 354;
	m_bFeverMode = false;
	m_bFeverDraw = false;
}

bool AirplaneGameScene::Input(float fETime)
{
	// ESC ������ ���Ӽ��� ȭ������ ���ư�
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}

	m_MousePos = JEngine::InputManager::GetInstance()->GetMousePoint();

	return false;
}

void AirplaneGameScene::Update(float fETime)
{
	if ((x - m_MousePos.x) != 0)
	{
		float theta = abs(atanf(((float)y - (float)m_MousePos.y) / ((float)x - (float)m_MousePos.x)));
		
		if (m_MousePos.x > x)
		{
			x += fETime * m_BulletSpeed * cosf(theta);
		}
		else
		{
			x -= fETime * m_BulletSpeed * cosf(theta);
		}
		if (m_MousePos.y > y)
		{
			y += fETime * m_BulletSpeed * sinf(theta);
		}
		else
		{
			y -= fETime * m_BulletSpeed * sinf(theta);
		}		
	}
	else
	{
		if (m_MousePos.y > y)
		{
			y += fETime * m_BulletSpeed;
		}
		else
		{
			y -= fETime * m_BulletSpeed;
		}
	}
	

	switch (m_eState)
	{
	case GAME_STATE_PLAY:
		m_fPlayTime += fETime;
		// ���ѽð� ������ ���ӿ���
		if (m_fPlayTime >= m_fPlayLimitTime)
		{
			m_fPlayTime = m_fPlayLimitTime;
			m_eState = GAME_STATE_OVER;
		}

		// �ǹ������� �������� �ǹ����
		if (m_iFeverScore >= m_iFeverScoreMax)
		{
			m_bFeverMode = true;
		}
		// �ǹ� �ð� ������ �ǹ� ��� ����
		if (m_fFeverTime > m_fFeverLimitTime)
		{
			m_bFeverMode = false;
			m_fFeverTime = 0.0f;
			m_iFeverScore = 0;
		}

		//  �ǹ� ��� 0.3�ʸ��� �����̴� ȿ��
		if (m_bFeverMode)
		{
			m_fFeverTime += fETime;
			m_fFeverAnimTime += fETime;
			if (m_fFeverAnimTime > 0.3f)
			{
				m_fFeverAnimTime = 0.0f;
				m_bFeverDraw = !m_bFeverDraw;
			}
		}
		else
		{
			m_bFeverDraw = false;
		}
		break;
	case GAME_STATE_OVER:
		m_fGameOverTime += fETime;
		if (m_fGameOverTime >= m_fGameOverLimitTime)
		{
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
		}
		break;
	default:
		break;
	}
}

void AirplaneGameScene::Draw(HDC hdc)
{
	// ���, �ϴ� �ð��� �׸���
	m_pBack->Draw(0, 0);
	m_pTimeBar->Draw(23, 620, m_fPlayTime / m_fPlayLimitTime, 1.0f);

	// �ǹ���� ������ �׸���
	if (m_bFeverMode)
	{
		m_pFeverBar1->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, (m_fFeverLimitTime - m_fFeverTime) / m_fFeverLimitTime, 1.0f);
	}
	else
	{
		m_pFeverBar1->Draw(20, 51, 1.0f, 1.0f, 0.0f, 0.0f, ((float)m_iFeverScore / (float)m_iFeverScoreMax), 1.0f);
	}

	

	switch (m_eState)
	{
	case GAME_STATE_PLAY:
		m_pFlight->Draw(m_MousePos);
		if (m_bFeverDraw)
			m_pFeverBack->Draw(0, 0);
		break;
	case GAME_STATE_OVER:
		// Ÿ�ӿ��� �̹��� �׸���
		m_pTimeOver->Draw(213, 350);
		break;
	default:
		break;
	}
	m_pBullet->Draw(x, y);
}

void AirplaneGameScene::Release()
{
}

bool AirplaneGameScene::OnClick()
{
	return false;
}

AirplaneGameScene::AirplaneGameScene()
{
}

AirplaneGameScene::~AirplaneGameScene()
{
}
