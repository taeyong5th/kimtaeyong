#pragma once

#define MAP_SIZE_WIDTH 45
#define MAP_SIZE_HEIGHT 30

#define WINDOW_SIZE_WIDTH (MAP_SIZE_WIDTH * 2)
#define WINDOW_SIZE_HEIGHT (MAP_SIZE_HEIGHT + 3)

#define SNAKE_DEFAULT_SPEED 200 // 뱀 기본 속도
#define SNAKE_DEFAULT_SPEED_UP_INTERVAL 10 // 음식 먹을때 마다 증가할 속도
#define SNAKE_DEFAULT_SPEED_MAX 50 // 뱀 최대 속도

#define SNAKE_CREATE_FOOD_INTERVAL 1000 // 음식 생성할 시간 간격

#define KEY_LEFT 'a'
#define KEY_RIGHT 'd'
#define KEY_UP 'w'
#define KEY_DOWN 's'

#define FOOD_MAX 10 // 음식 최대 개수
#define WALL_COUNT 50 // 벽 개수