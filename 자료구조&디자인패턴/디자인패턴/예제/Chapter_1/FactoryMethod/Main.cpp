#include "Game.h"

int main()
{
	MyGame* game = new MyGame();

	game->Initialized();
	game->Update();
	game->Finished();

	delete game;
}