#include "Gun.h"
#include "Character.h"

void Gun::specialAttack(Character& player, Character& monster)
{
	int bonusGold = monster.getGold() * 0.2;
	RED
		cout << "Ư���ɷ� �ߵ� : " << to_string(bonusGold) << " ��� ȹ��" << endl;
	ORIGINAL
		player.setGold(player.getGold() + bonusGold);
}

Gun::Gun()
{
}

Gun::~Gun()
{
}
