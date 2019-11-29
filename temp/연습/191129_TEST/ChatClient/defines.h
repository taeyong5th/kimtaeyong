#pragma once

enum GAME_STATE
{
	GAME_STATE_START_WAIT, // 게임 시작 및 및 서버 응답 대기
	GAME_STATE_WAIT, // 상대방 기다리는 중
	GAME_STATE_PLAY, // 내가 플레이하는 중
	GAME_STATE_OVER // 게임이 종료됨
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
	//int playerID; // black인지 white인지
	/*
			request				response		actionid
	0x00
	0x01 단순 연결 확인			SUCCESS/FAIL	get_isconnected
	0x02 흑백 색깔 배정 요청	black/white		get_playerID
	0x03 (x, y)위치에 돌을 놓음	board정보		get_board

	*/
	int action; // 유저가 어떤 행위를 하는지
	int dataSize;
	char data[BUF_SIZE];
};

struct OmokPoint
{
	int x;
	int y;
	int color;
};