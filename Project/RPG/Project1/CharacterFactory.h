#pragma once
#include <vector>
#include "JobClass.h"
#include "Singleton.h"

class CharacterFactory : public Singleton<CharacterFactory>
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