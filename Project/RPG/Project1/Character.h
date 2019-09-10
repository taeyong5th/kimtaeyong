#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Weapon.h"
#include "Bow.h"
#include "Gun.h"
#include "Dagger.h"
#include "Sword.h"

class Character
{
private:
	Weapon* mWeapon;
	MapDraw mMapDraw;

	string m_strName;
	int m_iAtkdmg;
	int m_iCurHealth;
	int m_iMaxHealth;
	int m_iEXP;
	int m_iMaxEXP;
	int m_iGetEXP;
	int m_iLv;
	int m_iType;
	int m_iGold;

public:
	string getName();
	void setName(string name);
	void inputName();
	int getCurHealth();
	void setCurHealth(int health);
	int getMaxHealth();
	int getAtkDmg();
	int getType();
	int getGetExp();
	int getGold();
	void setGold(int gold);
	void LvUp();
	void ShowPlayerInfo();
	void ShowChoice(int num);
	void LoadCharacter(ifstream& f);
	void ExpUp(Character& P2);
	void SaveInfo(ofstream& f);
	void LoadInfo(ifstream& f);
	void Attack(Character& P2);
	void setWeapon(Weapon* weapon);

	Character();
	~Character();
	
};