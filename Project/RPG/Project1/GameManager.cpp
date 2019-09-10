#include "GameManager.h"


GameManager::GameManager()
{
	GameOver = 0;
	Enemy = NULL;
}

GameManager::~GameManager()
{
	if (Enemy != NULL)
		delete[] Enemy;
}

void GameManager::Start()
{
	// 콘솔 창 크기 지정
	string cmd = "mode con: cols=" + to_string(WIDTH * 2) + "lines=" + to_string(HEIGHT + 1);
	system(cmd.c_str());

	while (!GameOver)
	{
		int height = HEIGHT * 0.3;
		m_MapDraw.DrawMidText("★ DungeonRPG ★", WIDTH, height);
		m_MapDraw.DrawMidText("New Game", WIDTH, height + 2);
		m_MapDraw.DrawMidText("Load Game", WIDTH, height + 4);
		m_MapDraw.DrawMidText("Game Exit", WIDTH, height + 6);
		int select = m_MapDraw.MenuSelectCursor(3, 2, 11, height + 2);
		m_MapDraw.DrawMidText("                    ", WIDTH, height);
		m_MapDraw.DrawMidText("                    ", WIDTH, height + 2);
		m_MapDraw.DrawMidText("                    ", WIDTH, height + 4);
		m_MapDraw.DrawMidText("                    ", WIDTH, height + 6);
		switch (select)
		{
		case 1:
			Loading();
			Main();
			break;
		case 2:
			Load();
			system("cls");
			Main();
			break;
		case 3:
			GameOver = 1;
			break;
		default:
			break;
		}
	}
}


void GameManager::Loading()
{
	m_MapDraw.gotoxy(WIDTH / 2, HEIGHT / 2);	
	cout << "플레이어 이름 입력 : ";
	Player.inputName();
	ifstream fs("Default.txt", ios::in);
	if (!fs.is_open())
	{
		cout << "플레이정보가 없습니다" << endl;
		GameOver = 1;
		system("pause");
		return;
	}
	Player.LoadCharacter(fs);	
	fs >> Stage;
	
	//Enemy = (Character*)malloc(sizeof(Character)*Stage);
	if (Enemy != NULL) delete[] Enemy;
	Enemy = new Character[Stage];
	for (int i = 0; i < Stage; i++)
	{
		string name;
		fs >> name;
		Enemy[i].setName(name);
		Enemy[i].LoadCharacter(fs);
	}
	fs.close();
}




void GameManager::Fight(Character * Player, Character * Enemy)
{
	int PlayerChoice, EnemyChoice;
	char tmp[256];
	int Count = 0;
	while (1)
	{
		system("cls");
		Player->ShowPlayerInfo();
		Enemy->ShowPlayerInfo();
		cout << Player->getName() << "입력" << endl;
		while (1)
		{
			cout << "가위 : 0, 바위 : 1, 보 : 2" << endl;
			cout << "입력 : ";
			cin >> PlayerChoice;
			if (PlayerChoice >= 0 && PlayerChoice <= 2)
				break;
			cout << "잘못입력 다시" << endl;
		}
		EnemyChoice = rand() % 3;
		Player->ShowChoice(PlayerChoice);
		Enemy->ShowChoice(EnemyChoice);
		if (PlayerChoice == EnemyChoice)
			cout << "무승부..." << endl;
		else if (PlayerChoice > EnemyChoice)
		{
			if (EnemyChoice == 가위 && PlayerChoice == 보)
				Enemy->Attack(*Player);
			else
				Player->Attack(*Enemy);
		}
		else
		{
			if (PlayerChoice == 가위 && EnemyChoice == 보)
				Player->Attack(*Enemy);
			else
				Enemy->Attack(*Player);
		}
		system("pause");
		if (Player->getCurHealth() <= 0)
		{
			system("cls");
			Player->ShowPlayerInfo();
			Enemy->ShowPlayerInfo();
			cout << Enemy->getName() << "승리!";
			Enemy->ExpUp(*Player);
			if (Player->getType() == PLAYER && Player->getGetExp() == 0)
			{
				cout << "Game Over" << endl;
				GameOver = 1;
				system("pause");
				return;
			}
			return;
		}
		else if (Enemy->getCurHealth() <= 0)
		{
			system("cls");
			Player->ShowPlayerInfo();
			Enemy->ShowPlayerInfo();
			cout << Player->getName() << "승리!";
			Player->ExpUp(*Enemy);
			return;
		}
	}
	return;
}

void GameManager::DunGeon()
{

	int height = HEIGHT * 0.2;
	int Select;
	while (!GameOver)
	{
		system("cls");
		m_MapDraw.DrawMidText("=====던전 입구=====", WIDTH, height);
		for (int i = 1; i <= Stage; i++) 
		{
			string dungeonName = to_string(i) + "층 던전 : [" + Enemy[i - 1].getName() + "]";
			m_MapDraw.DrawMidText(dungeonName, WIDTH, height + 2*i);
		}
		m_MapDraw.DrawMidText("돌아가기 ", WIDTH, height + 2 * (Stage+1));		
		
		Select = m_MapDraw.MenuSelectCursor(Stage + 1, 2, 6, height + 2);
		if (Select == Stage + 1)
			return;
		else if (Select >= 1 && Select <= Stage)
			Fight(&Player, &Enemy[Select - 1]);
	}
}

void GameManager::FileList()
{
	FILE* f;
	int Count = 0;
	char buf[256];
	for (int i = 1; i <= 10; i++)
	{
		sprintf(buf, "SaveFile%d.txt", i);
		f = fopen(buf, "r");
		cout << i << "번슬롯 : (파일여부 : ";
		if (f == NULL)
			cout << "X)" << endl;		
		else
		{
			cout << "O)" << endl;
			Count++;
			fclose(f);
		}
	}
	cout << "선택 : ";
}


void GameManager::Save()
{
	system("cls");
	cout << "=====Save=====" << endl;
	FileList();
	
	ofstream f;
	string buf;
	int Select;
	cin >> Select;
	if (Select > 10 || Select < 1)
	{
		cout << "잘못 선택 하셧습니다.";
		return;
	}
	buf = "SaveFile" + to_string(Select) + ".txt";
	f.open(buf, ios::out);
	Player.SaveInfo(f);
	f << Stage << endl;

	for (int i = 0; i < Stage; i++)
		Enemy[i].SaveInfo(f);
	
	f.close();
}



void GameManager::Load()
{
	ifstream fs("Default.txt", ios::in);
	if (!fs.is_open())
	{
		cout << "플레이정보가 없습니다" << endl;
		GameOver = 1;
		system("pause");
		return;
	}

	Player.LoadCharacter(fs);
	fs >> Stage;

	//Enemy = (Character*)malloc(sizeof(Character)*Stage);
	if (Enemy != NULL) delete[] Enemy;
	Enemy = new Character[Stage];
	for (int i = 0; i < Stage; i++)
	{
		string name;
		fs >> name;
		Enemy[i].setName(name);
		Enemy[i].LoadCharacter(fs);
	}
	fs.close();

	system("cls");
	cout << "=====Load=====" << endl;
	FileList();
	
	string buf;
	int Select;
	cin >> Select;
	if (Select > 10 || Select < 1)
	{
		cout << "잘못 선택 하셧습니다." << endl;
		return;
	}
	buf = "SaveFile" + to_string(Select) + ".txt";
	ifstream f;
	f.open(buf, ios::in);
	if (!f.is_open())
	{
		cout << "해당 저장 파일이 없습니다." << endl;
		system("pause");
		return;
	}
	Player.LoadInfo(f);
	f >> Stage;
	for (int i = 0; i < Stage; i++)
		Enemy[i].LoadInfo(f);
	f.close();
}

void GameManager::LoadWeapon()
{
	int Select;
	while (!GameOver)
	{
		int height = HEIGHT * 0.3;
		m_MapDraw.DrawMidText("★ Weapon Shop ★", WIDTH, height);
		m_MapDraw.DrawMidText("Bow", WIDTH, height + 2);
		m_MapDraw.DrawMidText("Dagger", WIDTH, height + 4);
		m_MapDraw.DrawMidText("Gun", WIDTH, height + 6);
		m_MapDraw.DrawMidText("Sword", WIDTH, height + 8);
		m_MapDraw.DrawMidText("Exit", WIDTH, height + 10);

		Select = m_MapDraw.MenuSelectCursor(5, 2, 10, height + 2);
		system("cls");
		Weapon* weapon;
		switch (Select)
		{
		case 1:				
			weapon = m_WeaponShop.showWeaponList(WEAPON_BOW);
			Player.setWeapon(weapon);
			break;
		case 2:
			weapon = m_WeaponShop.showWeaponList(WEAPON_DAGGER);
			Player.setWeapon(weapon);
			break;
		case 3:
			weapon = m_WeaponShop.showWeaponList(WEAPON_GUN);
			Player.setWeapon(weapon);
			break;
		case 4:
			weapon = m_WeaponShop.showWeaponList(WEAPON_SWORD);
			Player.setWeapon(weapon);
			break;
		case 5: // exit
			return;
		}
		system("cls");
	}

}

void GameManager::Main()
{	
	int Select;
	srand(time(NULL));
	m_MapDraw.DrawMidText("                              ", WIDTH / 2, HEIGHT / 2);
	
	while (!GameOver)
	{
		int height = HEIGHT * 0.3;
		m_MapDraw.DrawMidText("★ Menu ★", WIDTH, height);
		m_MapDraw.DrawMidText("Dungeon", WIDTH, height + 2);
		m_MapDraw.DrawMidText("Player Info", WIDTH, height + 4);
		m_MapDraw.DrawMidText("Monster Info", WIDTH, height + 6);
		m_MapDraw.DrawMidText("Weapon Shop", WIDTH, height + 8);
		m_MapDraw.DrawMidText("Save", WIDTH, height + 10);
		m_MapDraw.DrawMidText("Exit", WIDTH, height + 12);
		
		Select = m_MapDraw.MenuSelectCursor(6, 2, 10, height + 2);
		system("cls");
		switch (Select)
		{
		case 1:
			DunGeon(); // 던전 입장
			break;
		case 2:
			Player.ShowPlayerInfo();
			system("pause");
			break;
		case 3:			
			for (int i = 0; i < Stage; i++)
				Enemy[i].ShowPlayerInfo();
			system("pause");
			break;
		case 4: // weapon shop
			LoadWeapon();
			break;
		case 5: // save
			Save(); 
			break;
		case 6: // exit
			return;
		}
		system("cls");
	}
}
