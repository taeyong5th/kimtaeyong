#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Weapon.h"
#include "Bow.h"
#include "Dagger.h"
#include "Gun.h"
#include "Sword.h"

enum WeaponType
{
	WEAPON_BOW,
	WEAPON_DAGGER,
	WEAPON_GUN,
	WEAPON_SWORD
};

class WeaponShop
{
private:
	int bowCount;
	int daggerCount;
	int gunCount;
	int SwordCount;
	MapDraw m_MapDraw;
	Weapon* m_Bows;
	Weapon* m_Daggers;
	Weapon* m_Guns;
	Weapon* m_Swords;
public:
	Weapon* showWeaponList(WeaponType weaponType, int page = 0);
	WeaponShop();
	~WeaponShop();
};