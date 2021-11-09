#include "random_only.h"
#include "stdafx.h"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> MaxHeight(3, 10);
std::uniform_int_distribution<int> MaxRatio(135, 180);
std::uniform_int_distribution<int> minRatio(100, 125);
std::uniform_int_distribution<int> speed(5, 20);
std::uniform_int_distribution<int> boool(1, 2);
std::uniform_int_distribution<int> mazing(1, 16);

int random_only::get_MaxHeight()
{
	return MaxHeight(gen);
}

int random_only::get_MaxRatio()
{
	return MaxRatio(gen);
}

int random_only::get_minRatio()
{
	return minRatio(gen);
}

int random_only::get_speed()
{
	return speed(gen);
}

int random_only::get_boool()
{
	return boool(gen);
}

int random_only::get_mazing()
{
	return mazing(gen);
}
