#pragma once
#include "Weapon.h"

class Bow : public Weapon
{
public:
	
	void specialAttack(Character& player, Character& monster);
	Bow();
	~Bow();
};
