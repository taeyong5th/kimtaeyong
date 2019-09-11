#pragma once
#include "Mecro.h"
#include "MapDraw.h"
#include "Character.h"
#include "WeaponShop.h"

class GameManager
{
private:
	MapDraw m_MapDraw;
	WeaponShop m_WeaponShop;
	CharacterFactory * m_characterFactory;

	int GameOver;
	int Stage;
	Character Player, *Enemy;

	void Loading();
	void DunGeon();
	void Fight(Character* Player, Character* Enemy);
	void FileList();
	void Save();
	void Load();
	void LoadWeapon();
	void Main();

public:
	void Start();
	GameManager();
	~GameManager();
};