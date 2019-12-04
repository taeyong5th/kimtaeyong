#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"

unsigned WINAPI SendMsg(void* arg);
unsigned WINAPI RecvMsg(void* arg);

int m_iAction = OMOK_DO_NOTHING;

GAME_STATE g_eState = GAME_STATE_INTRO; // 게임 상태
PLAYER_COLOR g_PlayerColor; // 유저의 색상(검/흰)
OmokPoint g_Point; // 마우스로 클릭한 지점의 바둑판 좌표
int g_aBoard[BOARD_WIDTH][BOARD_HEIGHT]; // 바둑판 배열
std::string g_strStatus; // 하단에 출력할 게임 상태 텍스트

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
	//JEngine::UIManager::GetInstance()->AddButton(200, 200, "res//btn_start.bmp", std::bind(&TitleScene::OnClick, this));
	
	// 비트맵 이미지 초기화
	m_pBtnStart = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//btn_start.bmp");
	m_BtnStartRect.Set(300, 300, 300 + m_pBtnStart->GetWidth(), 300 + m_pBtnStart->GetHeight());	
	m_pBlock = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//block00.bmp");
	m_iBlockWidth = m_pBlock->GetWidth();
	m_iBlockHeight = m_pBlock->GetHeight();
	m_boardRect.Set(0, 0, m_iBlockWidth * BOARD_WIDTH, m_iBlockHeight * BOARD_HEIGHT);
	m_pStone[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_black.bmp");
	m_pStone[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_white.bmp");
	m_pWhiteBar = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//whitebar.bmp");

	// 오목판 초기화
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(g_aBoard[i], PLAYER_NONE, sizeof(int) * BOARD_HEIGHT);
	}
	ZeroMemory(&m_iMousePos, sizeof(m_iMousePos));
	
	// 게임 초기화
	g_eState = GAME_STATE_INTRO;
	g_PlayerColor = PLAYER_NONE;
	g_strStatus = "서버에 접속됨";

	//JEngine::UIManager::GetInstance()->AddButton(10, 20, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
	//m_pTitle->SetAnchor(JEngine::ANCHOR_CENTER);
	

	// 네트워크 처리
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox(m_hWnd, TEXT("WSAStartup 실패"), TEXT("접속오류"), MB_OK);
		exit(-1);
	}

	hSock = socket(PF_INET, SOCK_STREAM, 0);

	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servAdr.sin_port = htons(9000);
	int ret = connect(hSock, (SOCKADDR*)& servAdr, sizeof(servAdr));
	if (ret == SOCKET_ERROR)
	{
		MessageBox(m_hWnd, TEXT("서버 연결 실패"), TEXT("접속오류"), MB_OK);
		exit(-1);
	}

	hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)& hSock, 0, NULL);
	hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)& hSock, 0, NULL);
}

bool TitleScene::Input(float fETime)
{

	// 현재 마우스 위치정보를 받는다.
	m_iMousePos = JEngine::InputManager::GetInstance()->GetMousePoint();

	if (g_eState == GAME_STATE_INTRO)
	{
		// 시작버튼 클릭하면 서버에 시작 요청
		if (m_BtnStartRect.isPtin(m_iMousePos) && JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
		{
			m_iAction = OMOK_STARTABLE;
		}
	}
	else if(g_eState == GAME_STATE_PLAY)
	{
		// 마우스 클릭시 돌 놓기
		if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
		{
			if (m_boardRect.isPtin(m_iMousePos))
			{
				int x = m_iMousePos.x / m_iBlockWidth;
				int y = m_iMousePos.y / m_iBlockHeight;
				// 비어있는 공간이면 돌 놓음
				if (g_aBoard[x][y] == PLAYER_NONE)
				{
					//m_aBoard[x][y] = m_PlayerColor;
					g_Point.x = x;
					g_Point.y = y;
					g_Point.color = g_PlayerColor;
					m_iAction = OMOK_PUT_STONE;
				}
			}
			//JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME_SELECT);
		}
	}	
	
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
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

	if (g_eState == GAME_STATE_INTRO)
	{
		m_pBtnStart->Draw(300, 300);
	}
	// 놓여질 위치에 가상의 바둑돌을 그린다.
	else if (g_eState == GAME_STATE_PLAY)
	{
		m_pStone[g_PlayerColor]->Draw((m_iMousePos.x / m_iBlockWidth) * m_iBlockWidth, (m_iMousePos.y / m_iBlockHeight) * m_iBlockHeight);
	}
	
	// 이미 놓여진 돌을 전부 그린다.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			// 검은색 또는 흰색돌을 그림
			if (g_aBoard[i][j] == PLAYER_BLACK || g_aBoard[i][j] == PLAYER_WHITE)
			{
				m_pStone[g_aBoard[i][j]]->Draw(i * m_iBlockWidth, j * m_iBlockHeight);
			}
		}
	}

	m_pWhiteBar->Draw(0, 400);

	
	label.Init(g_strStatus, 0, 400, 0);
	label.Draw();
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

unsigned WINAPI SendMsg(void* arg)
{	
	SOCKET hSock = *((SOCKET*)arg);

	OmokPacketData request;
	//char nameMsg[BUF_SIZE];
	int result;
	while (true)
	{
		switch (m_iAction)
		{
		case OMOK_PLAYER_COLOR:
			//MessageBox(NULL, TEXT("GET COLOR"), TEXT("caption"), MB_OK);
			request.action = OMOK_PLAYER_COLOR;
			request.dataSize = 0;
			send(hSock, (char*)& request, sizeof(int) + sizeof(int), 0);
			m_iAction = OMOK_DO_NOTHING;
			break;
		case OMOK_STARTABLE:
			request.action = OMOK_STARTABLE;
			request.dataSize = sizeof(result);
			result = FALSE;
			memcpy(request.data, &result, sizeof(int));
			send(hSock, (char*)& request, sizeof(int) + sizeof(int) + request.dataSize, 0);
			g_strStatus = "상대방 준비를 기다리는 중...";
			g_eState = GAME_STATE_WAIT_CONN;
			m_iAction = OMOK_DO_NOTHING;
			break;
		case OMOK_PUT_STONE:
			//MessageBox(NULL, TEXT("PUT STONE"), TEXT("caption"), MB_OK);
			request.action = OMOK_PUT_STONE;
			request.dataSize = sizeof(g_Point);
			g_Point.color = g_PlayerColor;
			memcpy(request.data, &g_Point, sizeof(g_Point));
			send(hSock, (char*)& request, sizeof(int) + sizeof(int) + request.dataSize, 0);
			m_iAction = OMOK_DO_NOTHING;
			break;
		case OMOK_IS_MYTURN:
			request.action = OMOK_IS_MYTURN;
			request.dataSize = 0;
			send(hSock, (char*)& request, sizeof(int) + sizeof(int) + request.dataSize, 0);
			m_iAction = OMOK_DO_NOTHING;
			break;
		}
		
	}

	MessageBox(NULL, TEXT("SEND THREAD END"), TEXT("caption"), MB_OK);
	return 0;
}

unsigned __stdcall RecvMsg(void* arg)
{
	int hSock = *((SOCKET*)arg);
	char packet[BUF_SIZE];
	int dataSize;
	OmokPacketData* pResponse;
	PLAYER_COLOR* color;
	OmokPoint* pointlist;
	int* result;
	while (1)
	{
		dataSize = recv(hSock, packet, BUF_SIZE, 0);

		if (dataSize == -1)
		{
			//cout << "소켓 에러 종료" << endl;
			return -1;
		}
		else if (dataSize == 0)
		{
			//cout << "정상적인 종료" << endl;
			return 0;
		}
		pResponse = (OmokPacketData*)packet;

		switch (pResponse->action)
		{
		case OMOK_PLAYER_COLOR:
			color = (PLAYER_COLOR*)pResponse->data;
			if (*color == PLAYER_BLACK)
			{
				g_PlayerColor = PLAYER_BLACK;
				//MessageBox(NULL, TEXT("블랙"), TEXT("ㅇ"), MB_OK);
			}
			else if (*color == PLAYER_WHITE)
			{
				//g_eState = GAME_STATE_WAIT_CONN;
				g_PlayerColor = PLAYER_WHITE;
			}
			break;
		case OMOK_STARTABLE:
			result = (int*)pResponse->data;
			if (*result == TRUE)
			{
				g_strStatus = "시작!";
				m_iAction = OMOK_PLAYER_COLOR;
			}
			else
			{
				g_strStatus = "상대방을 찾는 중...";
			}
			break;
	/*	case OMOK_IS_MYTURN:
			result = (int*)pResponse->data;
			if (*result == TRUE)
			{
				g_eState = GAME_STATE_PLAY;
				g_strStatus = "내 차례";
			}
			else
			{
				g_strStatus = "상대방 차례";
				g_eState = GAME_STATE_WAIT;
			}
			break;*/
		case OMOK_PLAY:
			g_eState = GAME_STATE_PLAY;
			g_strStatus = "내 차례";
			//MessageBox(NULL, TEXT("내차례"), TEXT("ㅇ"), MB_OK);
			break;
		case OMOK_WAIT:
			g_strStatus = "상대방 차례";
			g_eState = GAME_STATE_WAIT;
			//MessageBox(NULL, TEXT("상대방차례"), TEXT("ㅇ"), MB_OK);
			break;
		case OMOK_BOARD_STATE:
			pointlist = (OmokPoint*)pResponse->data;
			for (int i = 0; i < pResponse->dataSize / sizeof(OmokPoint); ++i)
			{
				g_aBoard[pointlist[i].x][pointlist[i].y] = pointlist[i].color;
			}
			break;
		case OMOK_IS_WIN:
			result = (int*)pResponse->data;
			if (*result == TRUE)
			{
				g_strStatus = "승리";
			}
			else
			{
				g_strStatus = "패배";
			}			
			g_eState = GAME_STATE_OVER;
			break;
		default:
			break;
		}

	}

	return 0;
}