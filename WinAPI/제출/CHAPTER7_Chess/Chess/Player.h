#pragma once
#include "GameDefine.h"
#include "Piece.h"
#include <vector>

class Player
{
private:
	TEAM m_eTeam;
	std::vector<Piece*> m_pieces;

public:
	void init(TEAM team);
	void addPiece(Piece* piece);
	Player();
	~Player();
};