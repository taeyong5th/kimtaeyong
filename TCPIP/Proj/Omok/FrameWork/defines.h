#pragma once

enum SCENE_INDEX
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_GAME,
};

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