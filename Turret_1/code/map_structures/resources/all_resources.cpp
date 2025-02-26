
#include "all_resources.h"
#include "res_enum.h"


AllResources::AllResources(const int stone, const int iron, const int copper, const int silicon, const int coal, const int sulfur)
{
	allResources.emplace(ResType::STONE, stone);
	allResources.emplace(ResType::IRON, iron);
	allResources.emplace(ResType::COPPER, copper);
	allResources.emplace(ResType::SILICON, silicon);
	allResources.emplace(ResType::COAL, coal);
	allResources.emplace(ResType::SULFUR, sulfur);
}

AllResources::AllResources(const std::map<ResType, int> allResources) :
	allResources(allResources) { }
