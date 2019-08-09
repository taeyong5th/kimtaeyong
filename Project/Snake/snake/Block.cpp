#include "Block.h"

Block::Block(BLOCK_STATE state, int x, int y)
{
	// 블럭의 상태를 설정
	m_eState = state;

	// 블럭 모양을 설정
	setBlockState(state);

	// x, y 위치를 설정
	m_ix = x;
	m_iy = y;

	nextBlock = NULL;
}

Block::~Block()
{
}

bool Block::isCollision(const Block& block)
{
	if (m_ix == block.m_ix && m_iy == block.m_iy)
	{
		return true;
	}
	return false;
}

void Block::moveTo(int x, int y)
{
	undraw();
	m_ix = x;
	m_iy = y;
	draw();
}

void Block::draw()
{
	m_DrawManager.DrawPoint(m_shape, m_ix, m_iy);
}

void Block::undraw()
{
	m_DrawManager.DrawPoint(BLOCK_SHAPE_NOTHING, m_ix, m_iy);
}

int Block::getX()
{
	return m_ix;
}

int Block::getY()
{
	return m_iy;
}

void Block::setBlockState(BLOCK_STATE state)
{
	switch (state)
	{
	case BLOCK_STATE_WALL:
		m_shape = BLOCK_SHAPE_WALL;
		break;
	case BLOCK_STATE_FOOD:
		m_shape = BLOCK_SHAPE_FOOD;
		break;
	case BLOCK_STATE_SNAKE:
		m_shape = BLOCK_SHAPE_SNAKE;
		break;
	case BLOCK_STATE_SNAKE_HEAD:
		m_shape = BLOCK_SHAPE_SNAKE_HEAD;
		break;
	default:
		m_shape = BLOCK_SHAPE_WALL;
		break;
	}
}
