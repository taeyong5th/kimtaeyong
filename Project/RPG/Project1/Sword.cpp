#include "Sword.h"
#include "Character.h"

void Sword::specialAttack(Character& player, Character& monster)
{

	RED
		cout << "특수능력 발동 : 2배의 데미지" << endl;
	ORIGINAL
		monster.setCurHealth(monster.getCurHealth() - player.getAtkDmg());
}

Sword::Sword()
{
}

Sword::~Sword()
{
}
