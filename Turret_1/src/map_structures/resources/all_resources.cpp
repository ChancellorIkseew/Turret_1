
#include "all_resources.h"
#include "res_enum.h"


AllResources::AllResources(const uint32_t stone, const uint32_t iron, const uint32_t copper, const uint32_t silicon, const uint32_t coal, const uint32_t sulfur)
{
	allResources.emplace(ResType::STONE, stone);
	allResources.emplace(ResType::IRON, iron);
	allResources.emplace(ResType::COPPER, copper);
	allResources.emplace(ResType::SILICON, silicon);
	allResources.emplace(ResType::COAL, coal);
	allResources.emplace(ResType::SULFUR, sulfur);
}

AllResources::AllResources(const std::map<ResType, uint32_t> allResources) :
	allResources(allResources) { }
