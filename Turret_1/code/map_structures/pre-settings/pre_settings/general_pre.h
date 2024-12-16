#pragma once
#ifndef MAP_STR_GENERAL_PRE_H
#define MAP_STR_GENERAL_PRE_H

#include <map>
#include "util/parser/cpptoml.h"

struct GeneralPre
{
public:
	std::map<int, int> startBalance;

	void save(std::shared_ptr<cpptoml::table> root) const
	{

	}

	void load(std::shared_ptr<cpptoml::table> root)
	{

	}

};

#endif // MAP_STR_GENERAL_PRE_H
