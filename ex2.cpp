#include <iostream>
#include <vector>
#include <string> // for only getline function
#include <cstdlib>
#include <fstream>

std::string s_str = "-------------------\n";

void line()
{
	std::cout << s_str;
}

enum room
{
	living_room = 1,
	bathroom = 2,
	children_room = 4,
	kitchen = 8,
};

enum buildings
{
	house = 1,
	garage = 2,
	warehouse = 4,
	bathhouse = 8,
};

struct room_sq
{
	short type_r = 0;
	double sq = 0.f;
};

struct lvl
{
	std::vector <room_sq> r; // size of vector <room_sq> count of rooms
	double height = 0.f;
};

struct build
{
	int erection = 0;
	std::vector <lvl> floor;
	float area = 0.f;
	bool oven = true;
};


struct sites
{
	int num = 0;
	std::string owner = "";
	double area = 0.f;
	std::vector <build> bildings;
};

void b_floor(lvl* floor)
{
	std::cout << "Input count of rooms (1-4): ";
	int temp = 0;
	std::cin >> temp;
	floor->r.resize(temp);
	
	for (int i = 0; i < floor->r.size(); i++)
	{
		std::cout << "Input name of room to add on that floor\n(please use only small letter)\n";
		std::string str;
		std::cin >> str;

		if (str == "living") floor->r[i].type_r |= room::living_room;
		if (str == "bathroom") floor->r[i].type_r |= room::bathroom;
		if (str == "children") floor->r[i].type_r |= room::children_room;
		if (str == "kitchen") floor->r[i].type_r |= room::kitchen;

		std::cout << "Input area sq: ";
		std::cin >> floor->r[i].sq;
	}
}

void build_houme (build* houme)
{
	std::cout << "Input area of houme: ";
	houme->erection = buildings::house;
	std::cin >> houme->area;

	fl:

	std::cout << "Input floor of houme: ";
	int count_floor = 0;
	std::cin >> count_floor;
	if (count_floor < 0 || count_floor > 3)
	{
		std::cerr << "\aToo mach floors\nInput again (1 - 3 only)\n";
		goto fl;

	}
	houme->floor.resize(count_floor);
	for (int i = 0; i < count_floor; i++)
	{
		std::cout << "Floor: " << i << std::endl;
		b_floor(&houme->floor[i]);
	}
}

float free_sq(sites* site)
{
	double result = site->area;
	for (int i = 0; i < site->bildings.size(); i++)
	{
		result -= site->bildings[i].area;
	}
	return result;
}

void another_build(sites* site)
{
	dot_2:
	std::cout << "Home have in anycase\nDoes another bildings have in site?";
	std::string answere;
	std::cin >> answere;
	int count_b = 0;
	int index = 1;
	site->bildings.resize(index); // for houme
	if (answere == "no") return;
	else if (answere == "yes")
	{
		std::cout << "Garage?\n";
		std::cin >> answere;
		if (answere == "yes")
		{
			std::cout << "count: ";
			std::cin >> count_b;
			site->bildings.resize(site->bildings.size() + count_b);
			for (int i = index; i < count_b + index; i++)
			{

				site->bildings[i].erection |= buildings::garage;
				std::cout << "Sq: ";
				std::cin >> site->bildings[i].area;

			}
			index += count_b;
		}
		std::cout << "Wharehouse?\n";
		std::cin >> answere;
		if (answere == "yes")
		{
			std::cout << "count: ";
			std::cin >> count_b;
			site->bildings.resize(site->bildings.size() + count_b);
			for (int i = index; i < count_b + index; i++)
			{

				site->bildings[i].erection |= buildings::warehouse;
				std::cout << "Sq: ";
				std::cin >> site->bildings[i].area;

			}
		}
		std::cout << "Bathhouse?\n";
		std::cin >> answere;
		if (answere == "yes")
		{
			std::cout << "count: ";
			std::cin >> count_b;
			site->bildings.resize(site->bildings.size() + count_b);
			for (int i = index; i < count_b + index; i++)
			{

				site->bildings[i].erection |= buildings::bathhouse;
				std::cout << "Sq: ";
				std::cin >> site->bildings[i].area;

			}
		}
	}
	else 
	{
		std::cout << "Invalid answere";
		goto dot_2;
	}
	if (free_sq(site) < 0)
	{
		std::cout << "Ivalid area of buildings\nTry again\nNotice site area = " << site->area;
		goto dot_2;
	}
}	

void set_build(sites* site)
{
	std::cout << "Site " << site->num << std::endl;
	std::cout << "Input square of area: ";
	std::cin >> site->area;
	std::cout << "Input surname owner's: ";
	std::cin >> site->owner;
	line();
	another_build(site);
	line();
	build_houme(&site->bildings[0]);
	line();
}

void write_in_files(sites* site)
{
	std::string path = "site" + std::to_string(site->num) + ".txt";
	std::ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		std::cerr << "File isn't open\n";
		return;
	}
	file << s_str;
	file << "Site #" << site->num << std::endl;
	file << "Owner: " << site->owner << std::endl;
	file << "Square of site " << site->area << std::endl;
	file << "Square occupied bildings " << free_sq(site) << std::endl;
	file << s_str;
	file << "House have " << site->bildings[0].floor.size() << " floors\n";
	for (int i = 0; i < site->bildings[0].floor.size(); i++)
	{
		file << "floor " << i << " have:" << std::endl;
		file << site->bildings[0].floor[i].r.size() << " rooms.\n";
		file << "Height floor = " << site->bildings[0].floor[i].height << std::endl;
		float square = 0.f;

		for (int c = 0; c < site->bildings[0].floor[i].r.size(); c++)
		{
			file << (site->bildings[0].floor[i].r[c].type_r & room::bathroom ? "Bathroom " : "");
			file << (site->bildings[0].floor[i].r[c].type_r & room::children_room ? "Children room " : "");
			file << (site->bildings[0].floor[i].r[c].type_r & room::kitchen ? "Kitchen " : "");
			file << (site->bildings[0].floor[i].r[c].type_r & room::living_room ? "Living room " : "");
			square += site->bildings[0].floor[i].r[c].sq;
			
		}
		file << std::endl;
		file << "Total square of " << i << " floor = " << square << std::endl;
	}
	file << (site->bildings[0].oven ? "Have oven" : "Don't have oven") << std::endl;
	for (int i = 1; i < site->bildings.size(); i++)
	{
		if (site->bildings[i].erection & buildings::bathhouse)
		{
			file << s_str;
			file << "Bathhouse:\n"
				<< (site->bildings[i].oven ? "Have oven" : "Don't have oven") << std::endl
				<< "sq : " << site->bildings[i].area << std::endl;
		}
		if (site->bildings[i].erection & buildings::garage)
		{
			file << s_str;
			file << "Garage. sq: " << site->bildings[i].area << std::endl;
		}
		if (site->bildings[i].erection & buildings::warehouse)
		{
			file << s_str;
			file << "Warehouse. sq: " << site->bildings[i].area << std::endl;
		}
	}
	file << s_str;
	file.close();
}

int main()
{
	std::cout << "Welcome to village\n";
	line();
	std::vector <sites> village;

	dot_1:
	std::cout << "Input chek to see sites\nor input add to add sites\n->";
	std::string temp_str;
	std::cin >> temp_str;

	if (temp_str == "chek" || temp_str == "list")
	{
		line();
		if (village.size() == 0)
		{
			std::cout << "Nothing sites" << std::endl;
			return 0;
		}
		else {
			std::cout << village.size() << " sites in village" << std::endl;
			for (int i = 0; i < village.size(); i++)
			{
				std::cout << i + 1<< " site. Owner: " << village[i].owner << " sq: " << village[i].area << std::endl;
			}
			std::cout << "input num of site for check";
			int num = 0;
			std::cin >> num;
		}

	}
	else if (temp_str == "add")
	{
		line();
		int sz = village.size();
		village.resize(sz + 1); // add site on village
		village[sz].num = sz;
		set_build(&village[sz]); // set builds on one site
		write_in_files(&village[sz]); // save info about some site on files
	}
	line();
	goto dot_1;
}