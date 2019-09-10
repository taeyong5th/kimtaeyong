#include "CharacterFactory.h"

CharacterFactory::~CharacterFactory()
{
	jobs.clear();
	weapons.clear();
}

Weapon* CharacterFactory::CreateWeapon(WeaponType type)
{
	switch (type)
	{
	case WEAPON_BOW:
		return new Bow();
	case WEAPON_DAGGER:
		return new Dagger();
	case WEAPON_GUN:
		return new Gun();
	case WEAPON_SWORD:
		return new Sword();
	default:
		return nullptr;
	}
}

JobClass* CharacterFactory::CreateJobClass(JobClassType type)
{
	switch (type)
	{
	case CLASS_KNIGHT:
		return new Knight();
	case CLASS_ARCHER:
		return new Archer();
	case CLASS_HUNTER:
		return new Hunter();
	default:
		return nullptr;
	}
}

void CharacterFactory::AddJobClass(JobClass* job)
{
	jobs.push_back(job);
}

void CharacterFactory::AddWeapon(Weapon* weapon)
{
	weapons.push_back(weapon);
}
