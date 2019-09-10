#include "Weapon.h"
#include "Character.h"

void Weapon::setProperty(string type, string name, int sellprice, int atkdmg)
{
	m_strType = type;
	m_strName = name;
	m_iPrice = sellprice;
	m_iAtkdmg = atkdmg;
}

string Weapon::getType()
{
	return m_strType;
}

string Weapon::getName()
{
	return m_strName;
}

int Weapon::getPrice()
{
	return m_iPrice;
}

int Weapon::getAtkDmg()
{
	return m_iAtkdmg;
}

Weapon::Weapon()
{
}

Weapon::~Weapon()
{
}
