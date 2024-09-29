
#include <iostream>
#include <fstream>
#include <string>

#include "t1_time.h"


int t1::time::time = 0;
int t1::time::waveNumber = 0;

void t1::time::loadTime(const std::string& folder)
{
	std::string file = "saves/" + folder + "/time.txt";

	std::ifstream fin;
	fin.open(file);
	if (fin.is_open())
	{
		fin >> waveNumber >> time;
	}
	fin.close();

	std::cout << "Load time and wave_num works" << '\n';
}

void t1::time::saveTime(const std::string& folder)
{
	std::string file = "saves/" + folder + "/time.txt";

	std::ofstream fout;
	fout.open(file);
	fout << waveNumber << " " << time;
	fout.close();

	std::cout << "Save time and wave_num works" << '\n';
}