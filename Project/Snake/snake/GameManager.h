#pragma once
#include "Mecro.h"
#include "GameDefine.h"
#include "MapDraw.h"
#include "Snake.h"

enum MAIN_MENU
{
	MAIN_MENU_PLAY = 1,
	MAIN_MENU_EXIT
};

class GameManager
{
private:
	int m_iWidth;
	int m_iHeight;
	int m_iScore;
	MapDraw m_MapDraw;
	Snake m_Snake;
	Block *m_foods; // food list
	Block *m_walls; // wall list

// ������, �Ҹ���
public:
	GameManager();
	~GameManager();
	void start(); // ������ �����Ѵ�.

private:
	void init(); // ���� ���� ���� �ʱ�ȭ �Ѵ�.	
	void release();
	void play(); // ������ �÷����Ѵ�.
	void gameOver(); // ���� ����
	void printSocre(int score); // ������ �ϴܿ� ǥ���Ѵ�.

	bool isMapCollision(int x, int y); // �� �׵θ��� �΋H������ �˻�

	Block* makeBlock(BLOCK_STATE state); // ���� �ϳ� �����.	
	void removeBlock(Block** head, Block* block); // head ����Ʈ���� block�� ����
	void removeAllBlock(Block* head); // head ����Ʈ���� ����� ��� block�� ����
	Block* getBlock(Block* head, int x, int y); // head ����Ʈ�� x, y��ġ�� �ִ� ���� ��ȯ
	void addBlock(Block** head, Block* block); // head ����Ʈ�� ���� �ϳ� �߰�
	int countBlock(Block* head); // head ����Ʈ�� block ���� ��ȯ	

	void setConsoleSize(int width = WINDOW_SIZE_WIDTH, int height = WINDOW_SIZE_HEIGHT); // �ܼ� ũ�⸦ �����Ѵ�.

};