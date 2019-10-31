#include "AirplaneGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include "FeverMode.h"
#include "Label.h"
#include "ScoreUI.h"
#include "ScoreData.h"

void AirplaneGameScene::Init(HWND hWnd)
{

	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameBack.bmp");
	m_pTimeBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//ColoredPaperTimeBar.bmp");
	m_pTimeOver = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//TimeOver.bmp");
	m_pFlight = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//FlightGameFlight.bmp");

	m_pTimeOver->SetAnchor(JEngine::ANCHOR_CENTER);
	m_pFlight->SetAnchor(JEngine::ANCHOR_CENTER);
	
	m_fPlayTime = 0.0f;
	m_fGameOverTime = 0.0f;
	m_fBulletGenTime = 0.0f;
	m_fStarGenTime = 0.0f;

	m_eState = GAME_STATE_PLAY;

	m_flight.init();
	BulletManager::GetInstance()->init();
	StarManager::GetInstance()->init();
	FeverMode::GetInstance()->init();
	ScoreUI::GetInstance()->init();
}

bool AirplaneGameScene::Input(float fETime)
{
	// ESC 누르면 게임선택 화면으로 돌아감
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
	{
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
	}

	// 현재 마우스 위치가 비행기의 위치
	if (m_eState == GAME_STATE_PLAY)
	{
		m_flight.setPos(JEngine::InputManager::GetInstance()->GetMousePoint());
	}	

	return false;
}

void AirplaneGameScene::Update(float fETime)
{
	switch (m_eState)
	{
	case GAME_STATE_PLAY:
		m_fPlayTime += fETime;
		// 제한시간 끝나면 게임오버
		if (m_fPlayTime >= m_fPlayLimitTime)
		{
			m_fPlayTime = m_fPlayLimitTime;
			m_eState = GAME_STATE_OVER;
		}
		// 일정시간마다 총알 생성
		m_fBulletGenTime += fETime;
		if (m_fBulletGenTime >= m_fBulletGenLimitTime)
		{
			BulletManager::GetInstance()->createBullet(m_flight.getPoint());
			m_fBulletGenTime = 0.0f;
		}
		BulletManager::GetInstance()->update(fETime, m_flight);

		// 일정시간마다 별 생성
		m_fStarGenTime += fETime;
		if (FeverMode::GetInstance()->isFeverMode())
		{
			if (m_fStarGenTime >= (m_fStarGenLimitTime / 3.0f))
			{
				StarManager::GetInstance()->createStar(m_flight.getPoint());
				m_fStarGenTime = 0.0f;
			}
		}
		else
		{
			if (m_fStarGenTime >= m_fStarGenLimitTime)
			{
				StarManager::GetInstance()->createStar(m_flight.getPoint());
				m_fStarGenTime = 0.0f;
			}
		}
		StarManager::GetInstance()->update(fETime, m_flight);

		// 피버모드
		FeverMode::GetInstance()->update(fETime);

		// 비행기 업데이트
		m_flight.update(fETime);
		
		break;
	case GAME_STATE_OVER:
		m_fGameOverTime += fETime;
		if (m_fGameOverTime >= m_fGameOverLimitTime)
		{
			int bestScore = ScoreData::GetInstance()->loadScore(AIRPLANE_BEST_SCORE);
			if (m_flight.getScore() > bestScore)
			{
				ScoreData::GetInstance()->saveScore(AIRPLANE_BEST_SCORE, m_flight.getScore());
			}
			JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
		}
		break;
	default:
		break;
	}
}

void AirplaneGameScene::Draw(HDC hdc)
{
	// 배경, 하단 시간바 그리기
	m_pBack->Draw(0, 0);
	m_pTimeBar->Draw(23, 620, m_fPlayTime / m_fPlayLimitTime, 1.0f);

	FeverMode::GetInstance()->draw();
	StarManager::GetInstance()->draw(); 
	BulletManager::GetInstance()->draw();	
	ScoreUI::GetInstance()->draw(180, 20); 
	m_flight.draw();

	switch (m_eState)
	{
	case GAME_STATE_PLAY:
		break;
	case GAME_STATE_OVER:
		// 타임오버 이미지 그리기
		m_pTimeOver->Draw(213, 350);
		break;
	default:
		break;
	}
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
