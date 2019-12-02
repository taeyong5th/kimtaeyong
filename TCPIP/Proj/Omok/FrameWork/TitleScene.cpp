#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"


unsigned WINAPI SendMsg(void* arg);
unsigned WINAPI RecvMsg(void* arg);

int m_iAction = OMOK_DO_NOTHING;

GAME_STATE m_eState = GAME_STATE_INTRO;
PLAYER_COLOR m_PlayerColor;
OmokPoint g_Point;
int m_aBoard[BOARD_WIDTH][BOARD_HEIGHT];

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
	
	m_eState = GAME_STATE_INTRO;

	m_pBtnStart = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//btn_start.bmp");
	m_BtnStartRect.Set(300, 300, 300 + m_pBtnStart->GetWidth(), 300 + m_pBtnStart->GetHeight());	

	m_pBlock = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//block00.bmp");
	m_iBlockWidth = m_pBlock->GetWidth();
	m_iBlockHeight = m_pBlock->GetHeight();
	m_boardRect.Set(0, 0, m_iBlockWidth * BOARD_WIDTH, m_iBlockHeight * BOARD_HEIGHT);

	m_pStone[0] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_black.bmp");
	m_pStone[1] = JEngine::ResoucesManager::GetInstance()->GetBitmap("res//stone_white.bmp");

	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		memset(m_aBoard[i], PLAYER_NONE, sizeof(int) * BOARD_HEIGHT);
	}

	ZeroMemory(&m_iMousePos, sizeof(m_iMousePos));

	// ���� �÷��̾��� �� ����
	m_PlayerColor = PLAYER_NONE;

	//JEngine::UIManager::GetInstance()->AddButton(10, 20, "OnSelect.bmp", std::bind(&TitleScene::OnClick, this));
	//m_pTitle->SetAnchor(JEngine::ANCHOR_CENTER);


	// ��Ʈ��ũ ó��
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		MessageBox(m_hWnd, TEXT("WSAStartup ����"), TEXT("���ӿ���"), MB_OK);
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
		MessageBox(m_hWnd, TEXT("���� ���� ����"), TEXT("���ӿ���"), MB_OK);
		exit(-1);
	}
}

bool TitleScene::Input(float fETime)
{

	// ���� ���콺 ��ġ������ �޴´�.
	m_iMousePos = JEngine::InputManager::GetInstance()->GetMousePoint();

	if (m_eState == GAME_STATE_INTRO)
	{
		// ���۹�ư Ŭ���ϸ� ������ ���� ���� ��û
		if (m_BtnStartRect.isPtin(m_iMousePos) && JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
		{
			hSndThread = (HANDLE)_beginthreadex(NULL, 0, SendMsg, (void*)& hSock, 0, NULL);
			hRcvThread = (HANDLE)_beginthreadex(NULL, 0, RecvMsg, (void*)& hSock, 0, NULL);
			m_iAction = OMOK_PLAYER_COLOR;
		}
	}
	else if(m_eState == GAME_STATE_PLAY)
	{
		// ���콺 Ŭ���� �� ����
		if (JEngine::InputManager::GetInstance()->isKeyUp(VK_LBUTTON))
		{
			if (m_boardRect.isPtin(m_iMousePos))
			{
				int x = m_iMousePos.x / m_iBlockWidth;
				int y = m_iMousePos.y / m_iBlockHeight;
				// ����ִ� �����̸� �� ����
				if (m_aBoard[x][y] == PLAYER_NONE)
				{
					//m_aBoard[x][y] = m_PlayerColor;
					g_Point.x = x;
					g_Point.y = y;
					g_Point.color = m_PlayerColor;
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
	// �������� �׸���.
	for (int i = 0; i < BOARD_WIDTH; ++i)
	{
		for (int j = 0; j < BOARD_HEIGHT; ++j)
		{
			m_pBlock->DrawBitblt(i * m_iBlockWidth, j * m_iBlockHeight);			
		}
	}

	if (m_eState == GAME_STATE_INTRO)
	{
		m_pBtnStart->Draw(300, 300);
	}
	else
	{
		// ������ ��ġ�� ������ �ٵϵ��� �׸���.
		if (m_eState == GAME_STATE_PLAY)
		{
			m_pStone[m_PlayerColor]->Draw((m_iMousePos.x / m_iBlockWidth) * m_iBlockWidth, (m_iMousePos.y / m_iBlockHeight) * m_iBlockHeight);
		}

		// �̹� ������ ���� ���� �׸���.
		for (int i = 0; i < BOARD_WIDTH; ++i)
		{
			for (int j = 0; j < BOARD_HEIGHT; ++j)
			{
				// ������ �Ǵ� ������� �׸�
				if (m_aBoard[i][j] == PLAYER_BLACK || m_aBoard[i][j] == PLAYER_WHITE)
				{
					m_pStone[m_aBoard[i][j]]->Draw(i * m_iBlockWidth, j * m_iBlockHeight);
				}
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
			MessageBox(NULL, TEXT("GET COLOR"), TEXT("caption"), MB_OK);
			request.action = OMOK_PLAYER_COLOR;
			request.dataSize = 0;
			send(hSock, (char*)& request, sizeof(int) + sizeof(int), 0);
			break;
		case OMOK_IS_STARTABLE:
			request.action = OMOK_IS_STARTABLE;
			request.dataSize = sizeof(result);
			result = FALSE;
			memcpy(request.data, &result, sizeof(int));
			send(hSock, (char*)& request, sizeof(int) + sizeof(int) + request.dataSize, 0);
			break;
		case OMOK_PUT_STONE:
			MessageBox(NULL, TEXT("PUT STONE"), TEXT("caption"), MB_OK);
			request.action = OMOK_PUT_STONE;
			request.dataSize = sizeof(g_Point);
			memcpy(request.data, &g_Point, sizeof(g_Point));
			send(hSock, (char*)& request, sizeof(int) + sizeof(int) + request.dataSize, 0);
			break;
		}
		m_iAction = OMOK_DO_NOTHING;
	}

	MessageBox(NULL, TEXT("SEND THREAD END"), TEXT("caption"), MB_OK);
	return 0;
}

unsigned __stdcall RecvMsg(void* arg)
{

	int hSock = *((SOCKET*)arg);
	char packet[BUF_SIZE];
	int dataSize;
	OmokPacketData* prequest;
	PLAYER_COLOR* color;
	OmokPoint* pointlist;
	int* isStarted;
	while (1)
	{
		dataSize = recv(hSock, packet, BUF_SIZE, 0);

		if (dataSize == -1)
		{
			//cout << "���� ���� ����" << endl;
			return -1;
		}
		else if (dataSize == 0)
		{
			//cout << "�������� ����" << endl;
			return 0;
		}
		prequest = (OmokPacketData*)packet;

		switch (prequest->action)
		{
		case OMOK_PLAYER_COLOR:
			color = (PLAYER_COLOR*)prequest->data;
			if (*color == PLAYER_BLACK)
			{
				MessageBox(NULL, TEXT("��"), TEXT("����"), MB_OK);
				m_eState = GAME_STATE_WAIT_CONN;
				m_PlayerColor = PLAYER_BLACK;
			}
			else if (*color == PLAYER_WHITE)
			{
				MessageBox(NULL, TEXT("ȭ��Ʈ"), TEXT("����"), MB_OK);
				m_eState = GAME_STATE_WAIT_CONN;
				m_PlayerColor = PLAYER_WHITE;
			}
			break;
		case OMOK_IS_STARTABLE:
			isStarted = (int*)prequest->data;
			if (*isStarted == TRUE)
			{

			}
			else
			{

			}
			break;
		case OMOK_PLAY:
			m_eState = GAME_STATE_PLAY;
			break;
		case OMOK_WAIT:
			m_eState = GAME_STATE_WAIT;
			break;
		case OMOK_BOARD_STATE:
			pointlist = (OmokPoint*)prequest->data;
			for (int i = 0; i < prequest->dataSize / sizeof(OmokPoint); ++i)
			{
				m_aBoard[pointlist[i].x][pointlist[i].y] = pointlist[i].color;
			}
			break;
		default:
			break;
		}

	}

	return 0;
}