#include "Bow.h"
#include "Character.h"

void Bow::specialAttack(Character& player, Character& monster)
{
	RED
		cout << "Ư���ɷ� �ߵ� : ü�� 10% ȸ��" << endl;
	ORIGINAL
		player.setCurHealth(player.getCurHealth() + player.getMaxHealth() * 0.1);
		

}

Bow::Bow()
{
}

Bow::~Bow()
{
}
