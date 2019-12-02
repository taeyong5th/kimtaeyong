#pragma once

enum GAME_STATE
{
	GAME_STATE_INTRO, // ���� ���� ��
	GAME_STATE_WAIT, // ���� ������ ��ٸ�����
	GAME_STATE_PLAY, // ���� �÷����ϴ� ��(����)
	GAME_STATE_WAIT2, // ���� �� ���� ��ٸ��� ��(�����)	
	GAME_STATE_OVER // ������ �����
};

enum PLAYER_COLOR
{
	PLAYER_NONE = -1,
	PLAYER_BLACK,
	PLAYER_WHITE
};

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16

#define OMOK_DO_NOTHING			0x00
#define OMOK_PLAYER_COLOR		0x01
#define OMOK_IS_STARTABLE		0x02
#define OMOK_BOARD_STATE		0x03
#define OMOK_IS_WIN				0x04

#define BUF_SIZE 2048

struct OmokPacketData
{
	//int playerID; // black���� white����
	/*
			request				response		actionid
	0x00
	0x01 �ܼ� ���� Ȯ��			SUCCESS/FAIL	get_isconnected
	0x02 ��� ���� ���� ��û	black/white		get_playerID
	0x03 (x, y)��ġ�� ���� ����	board����		get_board

	*/
	int action; // ������ � ������ �ϴ���
	int dataSize; // -1 �̸� ����
	char data[BUF_SIZE];
};

struct OmokPoint
{
	int x;
	int y;
	PLAYER_COLOR color;
};