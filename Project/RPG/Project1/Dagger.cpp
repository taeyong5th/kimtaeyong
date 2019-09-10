#include "Dagger.h"
#include "Character.h"

void Dagger::specialAttack(Character& player, Character& monster)
{
	RED
		cout << "특수능력 발동 : 100의 추가 데미지" << endl;
	ORIGINAL
		monster.setCurHealth(monster.getCurHealth() - 100);
}

Dagger::Dagger()
{
}

Dagger::~Dagger()
{
}
