#include "Dagger.h"
#include "Character.h"

void Dagger::specialAttack(Character& player, Character& monster)
{
	RED
		cout << "Ư���ɷ� �ߵ� : 100�� �߰� ������" << endl;
	ORIGINAL
		monster.setCurHealth(monster.getCurHealth() - 100);
}

Dagger::Dagger()
{
}

Dagger::~Dagger()
{
}
