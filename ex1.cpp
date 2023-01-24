#include <iostream>
#include <fstream>
#include <vector>

struct client
{
    std::string name;
    std::string surname;
    std::string date;
    int value;
};

int main() {
    std::cout << "Decloration.exe\nInput comand:\n";
    std::string comand;
    std::cin >> comand;

    std::ifstream info("info.bin");
    int count = 0;
    info >> count;
    info.close();

    if(comand == "list")
    {
        std::ifstream dec ("dec.bin");
        std::vector <client> persons(count);
        for (int i = 0; i < count; i++)
        {
            dec >> persons[i].name;
            dec >> persons[i].surname;
            dec >> persons[i].date;
            dec >> persons[i].value;
            std::cout <<"#" << i << " " << persons[i].name << " " << persons[i].surname << " " << persons[i].date
            << " " << persons[i].value << std::endl;
        }


        dec.close();
    }
    else if (comand == "add"){

        std::ofstream info ("info.bin");
        std::ofstream dec ("dec.bin", std::ios::app);

        if(!dec.is_open()) std::cout << "NE open dec";
        if(!info.is_open()) std::cout << "NE open info";

        count++;
        info << count;

        std::string str;
        std::cin >> str;
        dec << str << ' ';
        std::cin >> str;
        dec << str << ' ';
        std::cin >> str;
        dec << str << ' ';
        std::cin >> str;
        dec << str << ' ';

        info.close();
        dec.close();
    }
    return 0;
}
