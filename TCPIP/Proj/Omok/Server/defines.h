#pragma once

enum GAME_STATE
{
	GAME_STATE_INTRO, // 게임 시작 전
	GAME_STATE_WAIT, // 상대방 접속을 기다리는중
	GAME_STATE_PLAY, // 내가 플레이하는 중(내턴)
	GAME_STATE_WAIT2, // 상대방 돌 놓기 기다리는 중(상대턴)	
	GAME_STATE_OVER // 게임이 종료됨
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
	//int playerID; // black인지 white인지
	/*
			request				response		actionid
	0x00
	0x01 단순 연결 확인			SUCCESS/FAIL	get_isconnected
	0x02 흑백 색깔 배정 요청	black/white		get_playerID
	0x03 (x, y)위치에 돌을 놓음	board정보		get_board

	*/
	int action; // 유저가 어떤 행위를 하는지
	int dataSize; // -1 이면 실패
	char data[BUF_SIZE];
};

struct OmokPoint
{
	int x;
	int y;
	PLAYER_COLOR color;
};