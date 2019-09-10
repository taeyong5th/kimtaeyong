#include "Character.h"

string Character::getName()
{
	return m_strName;
}

void Character::setName(string name)
{
	m_strName = name;
}

void Character::inputName()
{
	string name;
	cin >> name;
	m_strName = name;
}

void Character::setJobClass(JobClass* jobClass)
{
	m_jobClass = jobClass;
}

JobClass* Character::getJobClass()
{
	return m_jobClass;
}

int Character::getCurHealth()
{
	return m_iCurHealth;
}

void Character::setCurHealth(int health)
{
	m_iCurHealth = health;
	if (m_iCurHealth > m_iMaxHealth)
		m_iCurHealth = m_iMaxHealth;
}

int Character::getMaxHealth()
{
	return m_iMaxHealth;
}

int Character::getAtkDmg()
{
	return m_iAtkdmg;
}

int Character::getType()
{
	return m_iType;
}

int Character::getGetExp()
{
	return m_iGetEXP;
}

int Character::getGold()
{
	return m_iGold;
}

void Character::setGold(int gold)
{
	if (gold < 0) gold = 0;
	m_iGold = gold;
}



void Character::LvUp()
{
	int Num;
	cout << m_strName << "레벨업!" << endl;
	Num = rand() % (UPATTACKSTAT + 1) + 2;
	m_iAtkdmg += Num;
	cout << "공격력 " << Num << " 증가!!" << endl;
	Num = rand() % (UPHEALTHSTAT + 1) + 5;
	m_iMaxHealth += Num;
	cout << "생명력 " << Num << " 증가!!" << endl;
	m_iEXP = 0;
	m_iMaxEXP += m_iMaxEXP * 0.3;
	m_iLv++;
	m_iCurHealth = m_iMaxHealth;
}

void Character::ShowPlayerInfo()
{
	cout << "======" << m_strName << "(Lv" << m_iLv << ")======" << endl;
	cout << "공격력 = " << m_iAtkdmg << "  생명력 = " << m_iCurHealth << "/" << m_iMaxHealth << endl;
	cout << "경험치 = " << m_iEXP << "/" << m_iMaxEXP << "   GetEXP : " << m_iGetEXP << endl;
	cout << "골드 = " << m_iGold << endl;

	if (mWeapon != NULL)
	{
		cout << "==== 무기 ==== " << endl;
		cout << mWeapon->getType() << " / " << mWeapon->getName() << endl;
		cout << "공격력 :" << mWeapon->getAtkDmg() << endl;
	}
}

void Character::ShowChoice(int num)
{
	cout << m_strName << " : ";
	switch (num)
	{
	case 가위:
		cout << "가위!!" << endl;
		break;
	case 바위:
		cout << "바위!!" << endl;
		break;
	case 보:
		cout << "보!!" << endl;
		break;
	}
}

void Character::LoadCharacter(ifstream& f)
{
	f >> m_iAtkdmg;
	f >> m_iMaxHealth;
	m_iCurHealth = m_iMaxHealth;
	f >> m_iMaxEXP;
	m_iEXP = 0; 
	f >> m_iGetEXP;
	f >> m_iLv;
	f >> m_iType;
	f >> m_iGold;
	setWeapon(NULL);
}

void Character::ExpUp(Character& P2)
{
	int Num;
	system("cls");
	cout << m_strName << "승리!" << endl;
	cout << m_strName << "가 경험치 " << P2.m_iGetEXP << "를 얻었습니다" << endl;
	cout << m_strName << "가 골드 " << P2.m_iGold << "를 얻었습니다" << endl;
	
	m_iEXP += P2.m_iGetEXP;
	if (P2.m_iType == PLAYER)
	{
		P2.m_iEXP = 0;
		P2.m_iGetEXP = 0;
	}
	if (m_iEXP >=m_iMaxEXP)
		LvUp();

	if (m_iType == PLAYER)
		m_iGetEXP = m_iEXP;
	P2.m_iCurHealth = P2.m_iMaxHealth;
	m_iGold += P2.m_iGold;
	system("pause");
}

void Character::SaveInfo(ofstream& f)
{
	f << m_strName << " ";
	f << m_iAtkdmg << " ";
	f << m_iCurHealth << " ";
	f << m_iEXP << " ";
	f << m_iGetEXP << " ";
	f << m_iLv << " ";
	f << m_iMaxEXP << " ";
	f << m_iMaxHealth << " ";
	f << m_iType << " ";
	f << m_iGold << " ";
	if (mWeapon == NULL)
		f << "0" << endl;
	else
	{
		f << "1" << " ";
		f << mWeapon->getType() << " ";
		f << mWeapon->getName() << " ";
		f << mWeapon->getAtkDmg() << " ";
		f << mWeapon->getPrice() << endl;
	}
}

void Character::LoadInfo(ifstream& f)
{
	f >> m_strName;
	f >> m_iAtkdmg;
	f >> m_iCurHealth;
	f >> m_iEXP;
	f >> m_iGetEXP;
	f >> m_iLv;
	f >> m_iMaxEXP;
	f >> m_iMaxHealth;
	f >> m_iType;
	f >> m_iGold;

	int waeponExist;
	f >> waeponExist;
	Weapon* weapon = NULL;
	if (waeponExist == 1)
	{
		string type, name;
		int price, atk;
		f >> type >> name >> atk >> price;
		if (type == "Bow")
		{
			weapon = new Bow;			
		}
		else if (type == "Dagger")
		{
			weapon = new Dagger;
		}
		else if (type == "Gun")
		{
			weapon = new Gun;
		}
		else if (type == "Sword")
		{
			weapon = new Sword;
		}
		weapon->setProperty(type, name, price, atk);
	}
	setWeapon(weapon);
}

void Character::Attack(Character& P2)
{
	if (mWeapon != NULL) 
	{
		int Num = rand() % 5;
		if (Num > 1)
		{
			mWeapon->specialAttack(*this, P2);
		}
		P2.m_iCurHealth -= mWeapon->getAtkDmg();
	}

	P2.m_iCurHealth -= this->m_iAtkdmg;	
	if (P2.m_iCurHealth < 0)
		P2.m_iCurHealth = 0;
}

void Character::setWeapon(Weapon* weapon)
{
	if (mWeapon != NULL)
		delete mWeapon;

	if (weapon == NULL)
	{
		mWeapon = NULL;
		return;
	}
	
	if (m_iGold >= weapon->getPrice())
	{
		m_iGold -= weapon->getPrice();
		mWeapon = weapon;
	}
	else 
	{
		delete mWeapon;
		mWeapon = NULL;
	}
}

Character::Character()
{
	mWeapon = NULL;
	m_jobClass = NULL;	
}

Character::~Character()
{
	if (mWeapon != NULL)
		delete mWeapon;

	if (m_jobClass != NULL)
		delete m_jobClass;
}
