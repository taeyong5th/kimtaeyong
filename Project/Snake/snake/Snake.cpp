#include "Snake.h"

void Snake::addHead(int x, int y)
{
	// �� �Ӹ� ������ ���� �����.
	Block* newHead = NULL;
	newHead = new Block(BLOCK_STATE_SNAKE_HEAD, x, y);
	newHead->nextBlock = m_head;

	// ���� �Ӹ� ������ �������� �ٲٰ� �ٽ� �׸���.
	m_head->setBlockState(BLOCK_STATE_SNAKE);
	m_head->draw();

	// ���� ���� �Ӹ� ������ ���� �����ϰ� �׸���.
	m_head = newHead;
	m_head->draw();
}

void Snake::removeTail()
{
	// ���� �ٷ� �� �κ��� ã�´�.
	Block* prev = m_head;
	while (prev->nextBlock->nextBlock != NULL)
	{
		prev = prev->nextBlock;
	}
	// ���� �κ��� �����.
	prev->nextBlock->undraw();
	delete prev->nextBlock;
	prev->nextBlock = NULL;
}

void Snake::removeAllBlock(Block *head)
{
	if (head == NULL) return;
	removeAllBlock(head->nextBlock);
	delete head;
}

void Snake::init(int x, int y)
{
	// �� �Ӹ� ������ �����Ѵ�.
	m_head = new Block(BLOCK_STATE_SNAKE_HEAD, x, y);
	// �ӵ��� �����Ѵ�.
	m_iSpeed = SNAKE_DEFAULT_SPEED;
	// ���� ������ �����Ѵ�.
	setDirection(DIRECTION_NONE);
}

void Snake::release()
{
	removeAllBlock(m_head);
	m_head = NULL;
}

void Snake::setDirection(SNAKE_DIRECTION dir)
{
	if (m_eDirection == DIRECTION_LEFT && dir == DIRECTION_RIGHT) return;
	if (m_eDirection == DIRECTION_RIGHT && dir == DIRECTION_LEFT) return;
	if (m_eDirection == DIRECTION_UP && dir == DIRECTION_DOWN) return;
	if (m_eDirection == DIRECTION_DOWN && dir == DIRECTION_UP) return;
	
	m_eDirection = dir;
}

SNAKE_DIRECTION Snake::getDirection()
{
	return m_eDirection;
}

void Snake::action(SNAKE_ACTION action)
{

	// ���� �̵� ��ġ x, y�� ����
	int x = getX(), y = getY();
	switch (m_eDirection)
	{
	case DIRECTION_NONE:
		break;
	case DIRECTION_LEFT:
		x = getX() - 1;
		y = getY();
		break;
	case DIRECTION_RIGHT:
		x = getX() + 1;
		y = getY();
		break;
	case DIRECTION_UP:
		x = getX();
		y = getY() - 1;
		break;
	case DIRECTION_DOWN:
		x = getX();
		y = getY() + 1;
		break;
	default:
		break;
	}

	switch (action)
	{
	case SNAKE_ACTION_WAIT:
		break;
	case SNAKE_ACTION_MOVE:
		addHead(x, y);
		removeTail();
		break;
	case SNAKE_ACTION_EAT:
		addHead(x, y);
		break;
	default:
		break;
	}
}


void Snake::draw()
{
	Block *temp = m_head;
	while (temp != NULL)
	{
		temp->draw();
		temp = temp->nextBlock;
	}
}


bool Snake::isSelfCollision()
{
	Block* temp = m_head->nextBlock;

	// �������� �ϳ��� �浹�Ǵ°� �ִ��� �˻�
	while (temp != NULL)
	{
		if (temp->isCollision(*m_head))
			return true;
		temp = temp->nextBlock;
	}

	return false;
}

bool Snake::isCollisiton(int x, int y)
{
	Block* temp = m_head;
	while (temp != NULL)
	{
		if (temp->getX() == x && temp->getY() == y)
			return true;
		temp = temp->nextBlock;
	}
	return false;
}

int Snake::getX()
{
	if (m_head != NULL)
		return m_head->getX();
	else
		return -1;
}

int Snake::getY()
{
	if (m_head != NULL)
		return m_head->getY();
	else
		return -1;
}

void Snake::speedUp()
{
	if(m_iSpeed > SNAKE_DEFAULT_SPEED_MAX)
		m_iSpeed -= SNAKE_DEFAULT_SPEED_UP_INTERVAL;
}

int Snake::getSpeed()
{
	return m_iSpeed;
}

Snake::Snake()
{
	m_head = NULL;
}

Snake::~Snake()
{
	if (m_head != NULL)
	{
		removeAllBlock(m_head);
		m_head = NULL;
	}	
}
