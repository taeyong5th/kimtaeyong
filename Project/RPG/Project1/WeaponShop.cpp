#include "WeaponShop.h"

Weapon* WeaponShop::showWeaponList(WeaponType weaponType, int page)
{
	string search;
	switch (weaponType)
	{
	case WEAPON_BOW:
		search = "Bow";
		break;
	case WEAPON_DAGGER:
		search = "Dagger";
		break;
	case WEAPON_GUN:
		search = "Gun";
		break;
	case WEAPON_SWORD:
		search = "Sword";
		break;
	default:
		break;
	}

	string type, name;
	int atk, price;
	int count = 0;
	ifstream f;
	
	Weapon* weapons;
	Weapon* newWeapon = NULL;
	switch (weaponType)
	{
	case WEAPON_BOW:
		newWeapon = new Bow();
		count = bowCount;
		weapons = m_Bows;
		break;
	case WEAPON_DAGGER:
		newWeapon = new Dagger();
		count = daggerCount;
		weapons = m_Daggers;
		break;
	case WEAPON_GUN:
		newWeapon = new Gun();
		count = gunCount;
		weapons = m_Guns;
		break;
	case WEAPON_SWORD:
		newWeapon = new Sword();
		count = SwordCount;
		weapons = m_Swords;
		break;
	}

	if (page < 0) page = 0;
	if (page > count / 5) page = count / 5;

	int Select;
	int num = 0;
	int start = 5 * page;
	int end = (5 * page + 5) < count ? (5 * page + 5) : count;
	int height = HEIGHT * 0.1;
		
	m_MapDraw.DrawMidText(search + " List", WIDTH, height);		
	for (int i = 5 * page; i < end; i++)
	{
		type = weapons[i].getType();
		name = weapons[i].getName();
		price = weapons[i].getPrice();
		atk = weapons[i].getAtkDmg();
			
		string str = "이름 : " + name;
		string str2 = "공격력 : " + to_string(atk) + " 가격 : " + to_string(price);

		m_MapDraw.DrawMidText(str, WIDTH, height + 3*(num+1));
		m_MapDraw.DrawMidText(str2, WIDTH, height + 3*(num+1) + 1);

		num++;
	}

	m_MapDraw.DrawMidText("<<< 이전", WIDTH, height + 3 * (num + 1));
	m_MapDraw.DrawMidText("다음 >>>", WIDTH, height + 3 * (num + 1) + 3);
	m_MapDraw.DrawMidText("=== 종료 ===", WIDTH, height + 3 * (num + 1) + 6);

	Select = m_MapDraw.MenuSelectCursor(end - 5 * page + 3, 3, 6, height + 3);
	system("cls");

	if (Select == num + 1)
	{	
		delete newWeapon;
		return showWeaponList(weaponType, page - 1);
	}
	else if (Select == num + 2)
	{		
		delete newWeapon;
		return showWeaponList(weaponType, page + 1);
	}
	else if (Select == num + 3)
	{		
		delete newWeapon;
		return NULL;
	}
	else
	{
		newWeapon->setProperty(weapons[start + Select - 1].getType(), weapons[start + Select - 1].getName(), weapons[start + Select - 1].getPrice(), weapons[start + Select - 1].getAtkDmg());
		return newWeapon;
	}
}

WeaponShop::WeaponShop()
{	
	string type, name;
	int atk, price;	
	ifstream f;
	f.open("WeaponList.txt");
	if (!f.is_open())
	{
		cout << "무기 목록을 불러올 수 없습니다." << endl;
		system("pause");		
	}
	bowCount = daggerCount = gunCount = SwordCount = 0;
	while (!f.eof())
	{
		f >> type >> name >> atk >> price;
		if (type == "Bow") bowCount++;
		else if (type == "Dagger") daggerCount++;
		else if (type == "Gun") gunCount++;
		else if (type == "Sword") SwordCount++;		
	}
	f.close();

	m_Bows = new Bow[bowCount];
	m_Daggers = new Dagger[daggerCount];
	m_Guns = new Gun[gunCount];
	m_Swords = new Sword[SwordCount];

	f.open("WeaponList.txt");
	int i_bow = 0;
	int i_dagger = 0;
	int i_gun = 0;
	int i_sword = 0;
	while (!f.eof())
	{
		f >> type >> name >> atk >> price;
		if (type == "Bow")
			m_Bows[i_bow++].setProperty(type, name, atk, price);
		else if (type == "Dagger") 
			m_Daggers[i_dagger++].setProperty(type, name, atk, price);
		else if (type == "Gun") 
			m_Guns[i_gun++].setProperty(type, name, atk, price);
		else if (type == "Sword")
			m_Swords[i_sword++].setProperty(type, name, atk, price);			
	}
	f.close();
}

WeaponShop::~WeaponShop()
{
	delete[] m_Bows;
	delete[] m_Daggers;
	delete[] m_Guns;
	delete[] m_Swords;
}
