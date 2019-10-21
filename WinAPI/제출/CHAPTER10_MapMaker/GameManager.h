#pragma once
#include "GlobalDefine.h"
#include "Block.h"

class GameManager
{
public:
	GameManager();
	~GameManager();
	void start();
	void init();
	void initResource(HWND hWnd);	
	void load();
	void save();
private:
	int m_iRowCount, m_iColCount;
	// ���� ã�� �� �׷��� ��ġ
	const int m_iTop = 43;
	const int m_iLeft = 43;
	HWND m_hWnd;
	Block* m_Map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];
	bool m_bClickable; // ���� Ŭ�� ���� Ÿ�̸�
	int m_iBlockWidth;
	int m_iBlockHeight;
		
	//Ÿ��üũ��
	DWORD m_dwPrevTime;
	DWORD m_dwCurTime;
	float m_fDeltaTime;
	float m_fClickTime;	

	bool isValidRange(int x, int y); // x, y ���� Map �迭 ���� ������ �˻�
};

