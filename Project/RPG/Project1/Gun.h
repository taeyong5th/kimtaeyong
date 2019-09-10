#pragma once
#include "Weapon.h"

class Gun : public Weapon
{
public:

	void specialAttack(Character& player, Character& monster);
	Gun();
	~Gun();
};
