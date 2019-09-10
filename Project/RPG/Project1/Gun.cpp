#include "Gun.h"
#include "Character.h"

void Gun::specialAttack(Character& player, Character& monster)
{
	int bonusGold = monster.getGold() * 0.2;
	RED
		cout << "Æ¯¼ö´É·Â ¹ßµ¿ : " << to_string(bonusGold) << " °ñµå È¹µæ" << endl;
	ORIGINAL
		player.setGold(player.getGold() + bonusGold);
}

Gun::Gun()
{
}

Gun::~Gun()
{
}
