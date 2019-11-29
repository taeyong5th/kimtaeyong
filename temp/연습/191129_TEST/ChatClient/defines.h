#pragma once

enum GAME_STATE
{
	GAME_STATE_START_WAIT, // ���� ���� �� �� ���� ���� ���
	GAME_STATE_WAIT, // ���� ��ٸ��� ��
	GAME_STATE_PLAY, // ���� �÷����ϴ� ��
	GAME_STATE_OVER // ������ �����
};

enum OMOK_PLAYER_ID
{
	PLAYER_ID_NONE = -1,
	PLAYER_ID_BLACK,
	PLAYER_ID_WHITE
};

#define BOARD_WIDTH 16
#define BOARD_HEIGHT 16


#define GET_ISCONNECTED	0x01
#define GET_PLAYERID	0x02
#define GET_BOARD		0x03

#define BUF_SIZE 2048

#define COLOR_BLACK 0
#define COLOR_WHITE 1

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
	int dataSize;
	char data[BUF_SIZE];
};

struct OmokPoint
{
	int x;
	int y;
	int color;
};