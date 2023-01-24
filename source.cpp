#include <iostream>
#include <stdio.h>

bool shit (std::string str, std::string str_2)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != str_2[i]) return false;
    }
    return true;

}


bool compare(float value, float reference, float epsilon)
{
    return (value >= reference - epsilon) && (value <= reference + epsilon);
}

int main()
{
    float speed = 0.0f;
    float temp = speed;
    float temp_2 = 0.f;
    char pole[6];
    char spd_str[50] = "";
    do
    {
        std::cout << "Speed: " << spd_str << " mp\\h\n";
        std::cin >> pole;
        temp = std::atof(pole);
        temp_2 = speed + temp;
        std::sprintf(spd_str, "%.01f", speed);

        if (shit(spd_str,"150.0")) speed += temp;
        else
        {
            std::cout << "Max speed 150 mp\\h\n";
        }

        if (compare(speed, .0f, 0.01f)) {
            speed = 0;
        }

    } while (true);
    return 0;
}