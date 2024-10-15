
#include "all_resources.h"
#include "res_enum.h"


AllResources::AllResources(const int stone, const int iron, const int copper, const int silicon, const int coal, const int sulfur)
{
	allResources.emplace(RES_STONE, stone);
	allResources.emplace(RES_IRON, iron);
	allResources.emplace(RES_COPPER, copper);
	allResources.emplace(RES_SILICON, silicon);
	allResources.emplace(RES_COAL, coal);
	allResources.emplace(RES_SULFUR, sulfur);
}

AllResources::AllResources(const std::map<int, int> allResources)
{
	this->allResources = allResources;
}

AllResources::AllResources()
{

}