#pragma once
#include "Weapon.h"
#include "Bow.h"
#include "Gun.h"
#include "Dagger.h"
#include "Sword.h"

enum JobClassType
{
	CLASS_KNIGHT,
	CLASS_ARCHER,
	CLASS_HUNTER
};

class JobClass
{
private:
	Weapon* weapon;

public:
	void SetWeapon(Weapon* _weapon);
	virtual bool EquipCheck() = 0;

protected:
	Weapon* GetWeapon();
};

class Knight : public JobClass
{
public:
	virtual bool EquipCheck();
};

class Archer : public JobClass
{
public:
	virtual bool EquipCheck();
};

class Hunter : public JobClass
{
public:
	virtual bool EquipCheck();
};
