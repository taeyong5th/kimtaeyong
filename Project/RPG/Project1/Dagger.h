#pragma once
#include "Weapon.h"

class Dagger : public Weapon
{
public:

	void specialAttack(Character& player, Character& monster);
	Dagger();
	~Dagger();
};
