#include "Tank.h"
#include "TankManager.h"
#include "Astar.h"

LPCWSTR Tank::getShape()
{
	return m_aAnimations[m_iAnimIndex];
}

void Tank::init(int x, int y, RECT mapRect)
{
	m_ix = x;
	m_iy = y;
	m_MapRect = mapRect;
	m_iWidth = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getWidth() * multifly;
	m_iHeight = BitmapManager::GetInstance()->getBitmap(IMG_PLAYER_TANK_D0)->getHeight() * multifly;

	m_eState = MOVE_STATE_IDLE;
	m_ePrevState = MOVE_STATE_UP;
	m_bAutoMode = false;
	m_bShieldOn = false;
	m_bHoming = false;

	m_iAnimIndex = 7;

	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;
	m_fAnimTick = 0.0f;
	m_fBulletTick = 0.0f;
	m_fAutoMoveTick = 0.0f;
	m_fShieldTick = 0.0f;
	m_fShieldAnimTick = 0.0f;
	m_iHP = 1;
	m_BulletManager.clear();
}

void Tank::draw()
{	// �ǵ带 �׸���
	if (m_bShieldOn)
	{
		BitmapManager::GetInstance()->prepare(m_aShieldAnims[m_iShiledAnimIndex], m_ix, m_iy, multifly, multifly);
	}
	// ��ũ�� �׸���
	if (m_eTeam == TEAM_ALLY)
	{
		int x1 = (getRect().left - m_MapRect.left   ) / m_iWidth;
		int y1 = (getRect().top - m_MapRect.top ) / m_iHeight;
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex], m_ix, m_iy, multifly, multifly);
		//BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex], x1 * m_iWidth + m_MapRect.left, y1 * m_iHeight + m_MapRect.top, multifly, multifly);
	}
	else
	{
		BitmapManager::GetInstance()->prepare(m_aAnimations[m_iAnimIndex + 8], m_ix, m_iy, multifly, multifly);
	}	
	// �Ѿ��� �׸���.
	m_BulletManager.draw();
}

POINT Tank::update(Block* a_map[][MAP_HEIGHT], TankManager* enemyTanks)
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwPrevTime) / 1000.0f;
	m_dwPrevTime = m_dwCurTime;

	m_fAnimTick += m_fDeltaTime;
	m_fBulletTick += m_fDeltaTime;
	m_fShieldAnimTick += m_fDeltaTime;
	m_fAutoMoveTick += m_fDeltaTime;
	if (m_bShieldOn)
	{
		m_fShieldTick += m_fDeltaTime;
	}
	for (int i = 0; i < MAP_WIDTH; ++i)
		for (int j = 0; j < MAP_HEIGHT; ++j)
			if (a_map[i][j]->movable())
				a_map[i][j]->setData(BLOCK_TYPE_BLANK);
			

	// �ڵ����� ���������� �� ������ �� �Ҷ�
	if (m_bAutoMode && !m_bHoming)
	{
		if (m_fAutoMoveTick > 0.6f)
		{
			switch (m_aAutoMode[m_iAutoIndex])
			{
			case 0:
				m_eState = MOVE_STATE_LEFT;
				break;
			case 1:
				m_eState = MOVE_STATE_RIGHT;
				break;
			case 2:
				m_eState = MOVE_STATE_UP;
				break;
			case 3:
				m_eState = MOVE_STATE_DOWN;
				break;
			case 4:
			default:
				shootBullet();
				m_iAutoIndex = rand() % 9;
				break;
			}
			m_iAutoIndex = rand() % 9;
			m_fAutoMoveTick = 0.0f;
		}
	}
	// �ڵ����� ���� �����ϸ� ������ ��
	else if (m_bAutoMode && m_bHoming && enemyTanks->size() > 0)
	{
		int x1 = (m_ix - m_MapRect.left) / m_iWidth;
		int y1 = (m_iy - m_MapRect.top) / m_iHeight;
		int x2 = (enemyTanks->begin()->getRect().left - m_MapRect.left) / m_iWidth;
		int y2 = (enemyTanks->begin()->getRect().top - m_MapRect.top) / m_iHeight;

		POINT start = {x1, y1};
		POINT dest = { x2, y2 };
		AstarNode startNode(PointToKey(start), PointToKey(start), 0, 0);
	
		map<int, AstarNode> open_list;
		map<int, AstarNode> close_list;

		// close list�� ���۳�带 �ִ´�.
		close_list[PointToKey(start)] = startNode;
		// open list�� ���۳��� ����� ��带 �ִ´�.
		const int moveX[4] = { 1, -1, 0, 0 };
		const int moveY[4] = { 0, 0, 1, -1 };
		for (int i = 0; i < 4; ++i)
		{
			POINT p;
			p.x = start.x + moveX[i];
			p.y = start.y + moveY[i];
			// x, y�� �迭�� �����̸鼭 ��ֹ��� �ƴϸ�
			if (isValidPoint(p) && (a_map[p.x][p.y]->movable()))
			{
				AstarNode node(PointToKey(p), PointToKey(start), 1, calcH(p, dest));
				open_list[node.key()] = node;
			}
		}

		// open list�� ��������� ����.(ã������)
		while (open_list.size() > 0) {
			// open list���� f���� ���� ���� ��� (A)�� �����´�.
			vector<pair<int, AstarNode>> vec(open_list.begin(), open_list.end());
			sort(vec.begin(), vec.end(), compareAstar);
			AstarNode A = vec.begin()->second;
			
			// (A)�� close list�� �ְ�
			open_list.erase(A.key());
			close_list[A.key()] = A;
			
			// (A)�� ������ ���� ����.
			if (A.key() == PointToKey(dest)) break;

			// (A)�� ����� ���(B)�� open list�� �ִ´�.
			for (int i = 0; i < 4; ++i)
			{
				POINT p;
				p.x = keyToPoint(A.key()).x + moveX[i];
				p.y = keyToPoint(A.key()).y + moveY[i];
				// x, y�� �迭�� �����̸鼭 ��ֹ��� �ƴϸ�
				if (isValidPoint(p) && (a_map[p.x][p.y]->movable()))
				{
					AstarNode B(PointToKey(p), A.key(), A.g() + 1, calcH(p, dest));
					// ����� ���(B)�� �̹� close list�� ������ �ش� ���� ����
					if (close_list.count(B.key()) > 0)
					{
						continue;
					}
					// ����� ���(B)�� �̹� open list�� ������ f���� ���Ͽ� ���� ����� ������Ʈ
					if (open_list.count(B.key()) > 0)
					{
						if (B.f() < open_list[B.key()].f())
						{
							open_list[B.key()] = B;
						}
					}
					else
					{
						open_list[B.key()] = B;
					}
				}
			}
		}

		int key = PointToKey(dest);
		int from;
		while (true)
		{
			// �����ִ� ���� ���°�� 80% Ȯ���� �Ѿ˽��� ���
			if (close_list.count(key) <= 0)
			{
				if (rand() % 10 > 1)
					shootBullet();
				break;
			}
			from = key;			
			key = close_list[key].from();
			//a_map[keyToPoint(key).x][keyToPoint(key).y]->setData(BLOCK_TYPE_WATER);
			if (key == PointToKey(start)) 
			{
				if (m_fAutoMoveTick > 0.5f)
				{
					m_eState = direction(start, keyToPoint(from));
					m_fAutoMoveTick = 0.0f;
					if(rand() % 10 > 4)
						shootBullet();
				}
				//a_map[start.x][start.y]->setData(BLOCK_TYPE_FLAG);
				//a_map[keyToPoint(from).x][keyToPoint(from).y]->setData(BLOCK_TYPE_FOREST);
				break;
			}
		}
	}
	// Ű �������� �̹��� ������ȯ ó��
	if (m_ePrevState != m_eState)
	{
		switch (m_eState)
		{
		case MOVE_STATE_DOWN:
			m_iAnimIndex = 2;
			break;
		case MOVE_STATE_LEFT:
			m_iAnimIndex = 0;
			break;
		case MOVE_STATE_UP:
			m_iAnimIndex = 6;
			break;
		case MOVE_STATE_RIGHT:
			m_iAnimIndex = 4;
			break;
		}
	}
	// ��ũ �ִϸ��̼� ó��
	if (m_fAnimTick > 0.25f)
	{
		switch (m_eState)
		{
		case MOVE_STATE_LEFT:
			m_iAnimIndex = ++m_iAnimIndex % 2;
			break;
		case MOVE_STATE_DOWN:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 2;
			break;
		case MOVE_STATE_RIGHT:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 4;
			break;
		case MOVE_STATE_UP:
			m_iAnimIndex = ++m_iAnimIndex % 2 + 6;
			break;
		case MOVE_STATE_IDLE:
		default:
			break;
		}
		m_fAnimTick = 0.0f;
	}
	// ���� �̹��� �ִϸ��̼�
	if (m_fShieldAnimTick > 0.15f)
	{
		m_iShiledAnimIndex = ++m_iShiledAnimIndex % 2;
	}
	// �ǵ� ���� �ð� 4�� �� �ǵ岨��
	if (m_fShieldTick > 4.0f)
	{
		m_bShieldOn = false;
		m_fShieldTick = 0.0f;
	}


	// ���⿡ ���� �����δ�
	switch (m_eState)
	{
	case MOVE_STATE_DOWN:
		m_iy += PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_LEFT:
		m_ix -= PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_UP:
		m_iy -= PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	case MOVE_STATE_RIGHT:
		m_ix += PLAYER_SPEED * m_fDeltaTime;
		m_ePrevState = m_eState;
		break;
	}
	
	// ������ �浹�� �˻��ϰ� ��ġ�� �����Ѵ�.
	RECT rect;
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		for (int j = 0; j < MAP_HEIGHT; j++)
		{
			if (IntersectRect(&rect, &a_map[i][j]->getRect(), &getRect()))
			{
				switch (m_eState)
				{
				case MOVE_STATE_IDLE:
					break;	
				case MOVE_STATE_LEFT:
					m_ix = rect.right;
					break;
				case MOVE_STATE_RIGHT:
					m_ix = rect.left - m_iWidth;
					break;
				case MOVE_STATE_UP:
					m_iy = rect.bottom;
					break;
				case MOVE_STATE_DOWN:
					m_iy = rect.top - m_iHeight;
					break;
				default:
					break;
				}
			}
		}
	}
	// �� ������ ������ �ʵ��� �Ѵ�.
	m_ix = m_ix < m_MapRect.left ? m_MapRect.left : m_ix;
	m_iy = m_iy < m_MapRect.top ? m_MapRect.top : m_iy;
	m_ix = m_ix < m_MapRect.right - m_iWidth ? m_ix : m_MapRect.right - m_iWidth;
	m_iy = m_iy < m_MapRect.bottom - m_iHeight ? m_iy : m_MapRect.bottom - m_iHeight;

	// �Ѿ� ��ġ�� ������Ʈ�Ѵ�.
	m_BulletManager.update(a_map, enemyTanks);
	
	POINT p = {m_ix, m_iy};
	return p;
}

POINT Tank::getPOS()
{
	POINT p;
	p.x = m_ix;
	p.y = m_iy;
	return p;
}

RECT Tank::getRect()
{
	RECT rect;
	rect.top = m_iy + 3;
	rect.left = m_ix + 3;
	rect.bottom = m_iy + m_iHeight - 6;
	rect.right = m_ix + m_iWidth - 6;
	return rect;
}

bool Tank::setAutoMode(bool autoMode)
{
	m_bAutoMode = autoMode;
	return m_bAutoMode;
}

bool Tank::setHoming(bool homingMode)
{
	m_bHoming = homingMode;
	return m_bHoming;
}

bool Tank::setShield(bool shieldOn)
{
	m_bShieldOn = shieldOn;
	return m_bShieldOn;
}

int Tank::getHP()
{
	return m_iHP;
}

void Tank::setHP(int hp)
{
	if (m_bShieldOn) return;
	hp = hp < 0 ? 0 : hp;
	m_iHP = hp;
	if (m_iHP == 0)
		m_eState = MOVE_STATE_DIE;
}


void Tank::shootBullet()
{
	m_fBulletTick += m_fDeltaTime;
	if (m_fBulletTick > 0.45f)
	{
		m_fBulletTick = 0.0f;
		Bullet bullet;
		RECT rect = getRect();
		bullet.init((rect.left + rect.right) / 2, (rect.top + rect.bottom) / 2, m_MapRect);
		bullet.setState(m_ePrevState);
		bullet.setTeam(m_eTeam);
		m_BulletManager.add(bullet);
	}
}

Tank::Tank()
{
	m_aAnimations[0] = IMG_PLAYER_TANK_L0;
	m_aAnimations[1] = IMG_PLAYER_TANK_L1;
	m_aAnimations[2] = IMG_PLAYER_TANK_D0;
	m_aAnimations[3] = IMG_PLAYER_TANK_D1;
	m_aAnimations[4] = IMG_PLAYER_TANK_R0;
	m_aAnimations[5] = IMG_PLAYER_TANK_R1;
	m_aAnimations[6] = IMG_PLAYER_TANK_U0;
	m_aAnimations[7] = IMG_PLAYER_TANK_U1;
	
	m_aAnimations[8] = IMG_ENEMY_TANK_L0;
	m_aAnimations[9] = IMG_ENEMY_TANK_L1;
	m_aAnimations[10] = IMG_ENEMY_TANK_D0;
	m_aAnimations[11] = IMG_ENEMY_TANK_D1;
	m_aAnimations[12] = IMG_ENEMY_TANK_R0;
	m_aAnimations[13] = IMG_ENEMY_TANK_R1;
	m_aAnimations[14] = IMG_ENEMY_TANK_U0;
	m_aAnimations[15] = IMG_ENEMY_TANK_U1;
	
	m_aShieldAnims[0] = IMG_SHIELD_0;
	m_aShieldAnims[1] = IMG_SHIELD_1;


	for (int i = 0; i < 9; ++i)
	{
		m_aAutoMode[i] = i;
	}
}

Tank::~Tank()
{
}
