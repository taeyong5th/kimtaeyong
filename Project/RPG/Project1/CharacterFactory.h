#pragma once
#include <vector>
#include "JobClass.h"

class CharacterFactory
{
	vector<JobClass*> jobs;
	vector<Weapon*> weapons;

public:
	~CharacterFactory();

	Weapon* CreateWeapon(WeaponType type);
	JobClass* CreateJobClass(JobClassType type);

protected:
	void AddJobClass(JobClass* job);
	void AddWeapon(Weapon* weapon);

};