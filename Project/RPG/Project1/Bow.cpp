#include "Bow.h"
#include "Character.h"

void Bow::specialAttack(Character& player, Character& monster)
{
	RED
		cout << "특수능력 발동 : 체력 10% 회복" << endl;
	ORIGINAL
		player.setCurHealth(player.getCurHealth() + player.getMaxHealth() * 0.1);
		

}

Bow::Bow()
{
}

Bow::~Bow()
{
}
