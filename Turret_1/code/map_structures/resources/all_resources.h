#pragma once
#ifndef RESOURCES_H
#define RESOURCES_H

#include <map>

class AllResources
{
public:
	std::map<int, int> allResources;

	AllResources(const int stone, const int iron, const int copper, const int silicon, const int coal, const int sulfur);
	AllResources(const std::map<int, int> allResources);
	AllResources();
	~AllResources() = default;

};

#endif // RESOURCES_H
