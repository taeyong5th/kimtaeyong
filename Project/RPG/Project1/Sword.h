#pragma once
#include "Weapon.h"

class Sword : public Weapon
{
public:

	void specialAttack(Character& player, Character& monster);
	Sword();
	~Sword();
};
