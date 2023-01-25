#include <iostream> 
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

struct player
{
	std::string name ="";
	int healthpoinyt = 0;
	int armor = 0;
	int damage = 0;
	int pos_x = 0;
	int pos_y = 0;
	bool in_game = true; // false its flag to end game
};
void display(player* hero, player* enemy)
{
	
	for (int y = -1; y <= 20; y++)
	{
		for (int x = -1; x <= 20; x++)
		{
			if (x == -1 && y == -1) std::cout << "+";
			else if (x == 20 && y == 20) std::cout << "+";
			else if (x == -1 && y == 20)std::cout << "+";
			else if (x == 20 && y == -1) std::cout << "+";
			else if (x == -1 || x == 20) std::cout << "|";
			else if (y == -1 || y == 20) std::cout << " =";
			else
			{
				bool set_pos = true;
				if (hero->pos_x == x && hero->pos_y == y)
				{
					std::cout << 'P';
					set_pos = false;
				}
				for (int i = 0; i < 5; i++)
				{
					if (enemy[i].pos_x == x && enemy[i].pos_y == y && enemy[i].in_game)
					{
						if (set_pos)
						{
							std::cout << "E";
							set_pos = false;
						}
					}
				}
				if (set_pos)
				{
					std::cout << ".";
				}
				std::cout << ' ';
			}
		}
		std::cout << std::endl;
	}
	std::cout << "+-----|Status Hero|-----+\n";
	printf("|\tHP  :\t%i\t|\n", hero->healthpoinyt);
	printf("|\tDef :\t%i\t|\n", hero->armor);
	printf("|\tDMG :\t%i\t|\n", hero->damage);
	std::cout << "+-----------------------+\n";
}
void safe(player* hero, player* enemy)
{
	std::ofstream file;
	file.open("safe.bin", std::ios::binary);
	if (!file.is_open()) std::cout << "File isnt open\nComething breaked";
	{
		file.write((char*)&(hero->name), sizeof(hero->name));
		file.write((char*)&(hero->healthpoinyt), sizeof(hero->healthpoinyt));
		file.write((char*)&(hero->armor), sizeof(hero->armor));
		file.write((char*)&(hero->damage), sizeof(hero->damage));
		file.write((char*)&(hero->pos_x), sizeof(hero->pos_x));
		file.write((char*)&(hero->pos_y), sizeof(hero->pos_y));
		for (int i = 0; i < 5; i++)
		{
			file.write((char*)&(enemy[i].name), sizeof(enemy[i].name));
			file.write((char*)&(enemy[i].healthpoinyt), sizeof(enemy[i].healthpoinyt));
			file.write((char*)&(enemy[i].armor), sizeof(enemy[i].armor));
			file.write((char*)&(enemy[i].damage), sizeof(enemy[i].damage));
			file.write((char*)&(enemy[i].pos_x), sizeof(enemy[i].pos_x));
			file.write((char*)&(enemy[i].pos_y), sizeof(enemy[i].pos_y));
			file.write((char*)&(enemy[i].in_game), sizeof(enemy[i].in_game));
		}
		std::cout << "Saved" << std::endl;
	}
	file.close();
}
void load(player* hero, player* enemy)
{
	std::ifstream file;
	file.open("safe.bin", std::ios::binary);
	if (!file.is_open()) std::cout << "File isnt open\nChek files on PC";
	{
		file.read((char*)&(hero->name), sizeof(hero->name));
		file.read((char*)&(hero->healthpoinyt), sizeof(hero->healthpoinyt));
		file.read((char*)&(hero->armor), sizeof(hero->armor));
		file.read((char*)&(hero->damage), sizeof(hero->damage));
		file.read((char*)&(hero->pos_x), sizeof(hero->pos_x));
		file.read((char*)&(hero->pos_y), sizeof(hero->pos_y));
		for (int i = 0; i < 5; i++)
		{
			file.read((char*)&(enemy[i].name), sizeof(enemy[i].name));
			file.read((char*)&(enemy[i].healthpoinyt), sizeof(enemy[i].healthpoinyt));
			file.read((char*)&(enemy[i].armor), sizeof(enemy[i].armor));
			file.read((char*)&(enemy[i].damage), sizeof(enemy[i].damage));
			file.read((char*)&(enemy[i].pos_x), sizeof(enemy[i].pos_x));
			file.read((char*)&(enemy[i].pos_y), sizeof(enemy[i].pos_y));
			file.read((char*)&(enemy[i].in_game), sizeof(enemy[i].in_game));
		}
		std::cout << "Loaded" << std::endl;
	}
	file.close();
}
void move_p(player* hero, player* enemy)
{
	std::string move;
	std::cin >> move;
	system("cls");
	if (move == "w") hero->pos_y -= 1;
	else if (move == "s") hero->pos_y += 1;
	else if (move == "d") hero->pos_x += 1;
	else if (move == "a") hero->pos_x -= 1;
	else if (move == "safe") safe(hero, enemy);
	else if (move == "load") load(hero, enemy);
	if (hero->pos_y >= 20)
	{
		hero->pos_y = 19;
		goto point;
	}
	if (hero->pos_x >= 20)
	{
		hero->pos_x = 19;
		goto point;
	}
	if (hero->pos_y < 0)
	{
		hero->pos_y = 0;
		goto point;
	}
	if (hero->pos_x < 0)
	{
		hero->pos_x = 0;
		goto point;
	}
	if (false)
	{
	point:
		std::cout << "Wall. Movement can not to be\n";
	}
}

void fight(player* hero, player* enemy)
{
	for (int i = 0; i < 5; i++)
	{
		if (hero->pos_x == enemy[i].pos_x && hero->pos_y == enemy[i].pos_y)
		{
			enemy[i].armor -= hero->damage;
			if (enemy[i].armor < 0) enemy[i].armor = 0;
			enemy[i].healthpoinyt -= ((enemy[i].armor - hero->damage) < 0 ? (hero->damage - enemy[i].armor) : 0);
			if (enemy[i].healthpoinyt < 0)
			{
				std::cout << enemy[i].name << " is dead\n";
				enemy[i].in_game = false;
			}
			else if (enemy[i].healthpoinyt > 0)
			{
				std::cout << enemy[i].name << " took damage: " << hero->damage
					<< "HP: " << enemy[i].healthpoinyt
					<< " armor: " << enemy[i].armor
					<< std::endl;
			}
			return;
		}
	}
}
int main()
{
	//create enemy
	player enemy[5];
	for (int i = 0; i < 5; i++)
	{
		enemy[i].name = "Enemy #" + std::to_string(i);
		enemy[i].healthpoinyt = std::rand() % 150 + 50;
		enemy[i].armor = std::rand() % 50;
		enemy[i].damage = std::rand() & 30 + 15;
	}

	player hero;
	std::cout << "Create your hero!\nInput your name: ";
	std::cin >> hero.name;
	
	std::cout << "Input HP: ";
	std::cin >> hero.healthpoinyt;

	std::cout << "Input armor: ";
	std::cin >> hero.armor;

	std::cout << "Input damage: ";
	std::cin >> hero.damage;

	//set E and P
	hero.pos_x = std::rand() % 19;
	hero.pos_y = std::rand() % 19;
	
	for (int i = 0; i < 5; i++)
	{
		enemy[i].pos_x = std::rand() % 19;
		enemy[i].pos_y = std::rand() % 19;
	}
	do 
	{	
		display(&hero, enemy);
		move_p(&hero, enemy);
		fight(&hero, enemy);
		bool end_game = true;
		for (int i = 0; i < 5; i++)
		{
			if (enemy[i].in_game)
			{
				end_game = false;
				break;
			}
		}
		if (end_game)
		{
			break;
		}
	} while (hero.in_game);
	if (hero.in_game)
	{
		std::cout << "Congratulate player wins" << std::endl;
	}
	else {
		std::cout << "Lose";
	}
	return 0;
}