#pragma once
#include "Mecro.h"

class Character;

class Weapon
{
protected:
	string m_strType;
	string m_strName;
	int m_iPrice;
	int m_iAtkdmg;
public:
	virtual void  specialAttack(Character& player, Character& monster) = 0;
	void setProperty(string type, string name, int sellprice, int atkdmg);
	string getType();
	string getName();
	int getPrice();
	int getAtkDmg();
	
public:	
	Weapon();
	~Weapon();
};