#pragma once

enum GAME_STATE
{
	GAME_STATE_INTRO, // 게임 시작 전
	GAME_STATE_WAIT_CONN, // 상대방 접속을 기다리는중
	GAME_STATE_PLAY, // 내가 플레이하는 중(내턴)
	GAME_STATE_WAIT, // 상대방 돌 놓기 기다리는 중(상대턴)	
	GAME_STATE_OVER // 게임이 종료됨
};

enum PLAYER_COLOR
{
	PLAYER_NONE = -1,
	PLAYER_BLACK,
	PLAYER_WHITE
};

#define BOARD_WIDTH 8
#define BOARD_HEIGHT 8

#define OMOK_DO_NOTHING			0x00
#define OMOK_PLAYER_COLOR		0x01
#define OMOK_STARTABLE			0x02
#define OMOK_BOARD_STATE		0x03
#define OMOK_IS_WIN				0x04
#define OMOK_WAIT				0x05
#define OMOK_PLAY				0x06
#define OMOK_PUT_STONE			0x07
//#define OMOK_IS_MYTURN			0x08
#define OMOK_DISCONNECTED		0x09
//#define OMOK_PLAYER_FULL		0x10

#define BUF_SIZE 2048

struct OmokPacketData
{
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