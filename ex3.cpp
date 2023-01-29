#include <iostream>
#include <cmath>

struct vector 
{
	float x = 0.f;
	float y = 0.f;
};

void add()
{
	vector vec[2];
	std::cout << "add:\nInput 1st vector x,y: ";
	std::cin >> vec[0].x >> vec[0].y;
	std::cout << "Input 2st vector x,y: ";
	std::cin >> vec[1].x >> vec[1].y;
	vec[1].x += vec[0].x;
	vec[1].y += vec[0].y;
	std::cout << "Otained vector x: " << vec[1].x << " y: " << vec[1].y << std::endl;
}

void subtract()
{
	vector vec[2];
	std::cout << "subtract:\nInput 1st vector x,y: ";
	std::cin >> vec[0].x >> vec[0].y;
	std::cout << "Input 2st vector x,y: ";
	std::cin >> vec[1].x >> vec[1].y;
	vec[1].x -= vec[0].x;
	vec[1].y -= vec[0].y;
	std::cout << "Obtained vector x: " << vec[1].x << " y: " << vec[1].y << std::endl;
}
void scale()
{
	vector vec;
	int scale;
	std::cout << "scale:\nInput vector x,y: ";
	std::cin >> vec.x >> vec.y;
	std::cout << "scale value: ";
	std::cin >> scale;
	std::cout << "Result vector x: " << vec.x * scale << " y: " << vec.y * scale << std::endl;
}
void length()
{
	vector vec;
	std::cout << "length:\nInput vector x,y: ";
	std::cin >> vec.x >> vec.y;
	float result = std::sqrt(vec.x * vec.x + vec.y * vec.y);
	std::cout << "Length vector result (num): " << result << std::endl;
}
void normalize()
{
	vector vec;
	std::cout << "normalize:\nInput vector x,y: ";
	std::cin >> vec.x >> vec.y;
	float distanse = std::sqrt(vec.x * vec.x + vec.y * vec.y); //
	std::cout << "Normalize vector x: " << vec.x / distanse << " y: " << vec.y / distanse << std::endl;
}

int main() 
{

	std::cout << "Input operation at vector\n(add, subtract, scale, length, normalize):\n";
	std::string ans;
	std::cin >> ans;
	if (ans == "add") add();
	else if (ans == "subtract") subtract();
	else if (ans == "scale") scale();
	else if (ans == "length") length();
	else if (ans == "normalize") normalize();
	return 0;
}