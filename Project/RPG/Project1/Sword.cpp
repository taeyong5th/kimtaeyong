#include "Sword.h"
#include "Character.h"

void Sword::specialAttack(Character& player, Character& monster)
{

	RED
		cout << "Ư���ɷ� �ߵ� : 2���� ������" << endl;
	ORIGINAL
		monster.setCurHealth(monster.getCurHealth() - player.getAtkDmg());
}

Sword::Sword()
{
}

Sword::~Sword()
{
}
