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

// 생성자, 소멸자
public:
	GameManager();
	~GameManager();
	void start(); // 게임을 시작한다.

private:
	void init(); // 게임 설정 값을 초기화 한다.	
	void release();
	void play(); // 게임을 플레이한다.
	void gameOver(); // 게임 오버
	void printSocre(int score); // 점수를 하단에 표시한다.

	bool isMapCollision(int x, int y); // 맵 테두리에 부딫혔는지 검사

	Block* makeBlock(BLOCK_STATE state); // 블럭을 하나 만든다.	
	void removeBlock(Block** head, Block* block); // head 리스트에서 block을 삭제
	void removeAllBlock(Block* head); // head 리스트에서 연결된 모든 block을 삭제
	Block* getBlock(Block* head, int x, int y); // head 리스트에 x, y위치에 있는 블럭을 반환
	void addBlock(Block** head, Block* block); // head 리스트에 블럭을 하나 추가
	int countBlock(Block* head); // head 리스트의 block 개수 반환	

	void setConsoleSize(int width = WINDOW_SIZE_WIDTH, int height = WINDOW_SIZE_HEIGHT); // 콘솔 크기를 변경한다.

};