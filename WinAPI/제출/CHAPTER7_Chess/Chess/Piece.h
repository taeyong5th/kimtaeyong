#pragma once
#include <Windows.h>
#include <list>
#include <atlstr.h>
#include "GameDefine.h"
class Board;

class Piece
{
protected:
	LPCWSTR m_strBitmapName; // �ǽ��� ���
	BOARD_POSITION_X m_ix; // �ǽ��� ��ġ x
	BOARD_POSITION_Y m_iy; // �ǽ��� ��ġ y
	unsigned int m_imoveCount; // �ǽ��� ������ Ƚ��
	TEAM m_eTeam; // ���� or ����
	bool m_bChoose; // �� �ǽ��� ���� ����(Ŭ��)�Ǿ�����

public:
	virtual std::list<std::pair<BOARD_POSITION_X, BOARD_POSITION_Y>> getMovablePositions(Board* board) = 0; // piece�� �̵��� �� �ִ� �����ǥ ��ȯ
	
	Piece* move(Board* board, BOARD_POSITION_X x, BOARD_POSITION_Y y); // board�� x, y ��ġ�� �ǽ��� �̵�
	void drawMovablePositions(HDC hdc, int x, int y, Board *board); // piece�� �̵� ������ ���� �׸���.
	void draw(HDC hdc, int x, int y);
	std::pair<BOARD_POSITION_X, BOARD_POSITION_Y> getPosition();
	TEAM getTeam();
	Piece(LPCWSTR bitmapName, BOARD_POSITION_X x, BOARD_POSITION_Y y, TEAM team);
	virtual ~Piece();
};