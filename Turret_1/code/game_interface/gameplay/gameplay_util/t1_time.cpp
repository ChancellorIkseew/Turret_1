
#include <iostream>
#include <fstream>
#include <string>

#include "t1_time.h"


void t1::Time::loadTime(const std::string& folder)
{
	std::string file = "saves/" + folder + "/time.txt";

	std::ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		fin >> currentWave >> currentTime;
	}
	fin.close();

	std::cout << "Load time and wave_num works" << '\n';
}

void t1::Time::saveTime(const std::string& folder)
{
	std::string file = "saves/" + folder + "/time.txt";

	std::ofstream fout;
	fout.open(file);
	fout << currentWave << " " << currentTime;
	fout.close();

	std::cout << "Save time and wave_num works" << '\n';
}

void t1::Time::resetTime()
{
	currentTime = 0;
	currentWave = 0;
}

void t1::Time::setTime(const int time)
{
	currentTime = time;
}

void t1::Time::setWave(const int wave)
{
	currentWave = wave;
}

void t1::Time::timeRun(const int ticks)
{
	currentTime += ticks;
}

void t1::Time::setNextWave()
{
	++currentWave;
}
