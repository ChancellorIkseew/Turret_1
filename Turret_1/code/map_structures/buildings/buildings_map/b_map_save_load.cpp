

#include "buildings_map.h"

#include <iostream>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>


void BuildingsMap::save(cereal::BinaryOutputArchive& archive) const
{
	int num = 0;
	for (auto& line : buildingsMap)
		for (auto& building : line)
			if (building != nullptr)
				++num;

	archive(num);

	for (auto& line : buildingsMap)
		for (auto& building : line)
			if (building != nullptr)
				building->save(archive);
}

void BuildingsMap::load(cereal::BinaryInputArchive& archive)
{
	int num;
	archive(num);

	for (int i = 0; i < num; ++i)
	{
		
	}
}
