#include "JobClass.h"

void JobClass::SetWeapon(Weapon* _weapon)
{
	weapon = _weapon;
}

Weapon* JobClass::GetWeapon()
{
	return weapon;
}

/* Knight */
bool Knight::EquipCheck()
{
	Sword* sword = dynamic_cast<Sword*>(GetWeapon());
	Dagger* dagger = dynamic_cast<Dagger*>(GetWeapon());

	if (sword == NULL && dagger == NULL)
		return false;
	else
		return true;
}

/* Archer */
bool Archer::EquipCheck()
{
	Bow* bow = dynamic_cast<Bow*>(GetWeapon());

	if (bow == NULL)
		return false;
	else
		return true;
}

/* Hunter */
bool Hunter::EquipCheck()
{
	Gun* gun = dynamic_cast<Gun*>(GetWeapon());

	if (gun == NULL)
		return false;
	else
		return true;
}