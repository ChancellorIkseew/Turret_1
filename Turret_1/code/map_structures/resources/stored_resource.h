#pragma once
#ifndef STORED_RESOURCE_H
#define STORED_RESOURCE_H

#include "res_enum.h"
#include "typeinfo"

struct StoredResource
{
	StoredResource(ResType type, uint16_t quantity) :
		type(type), quantity(quantity) { }

	ResType type = ResType::NO_RESOURCES;
	uint16_t quantity = 0;
};

#endif // STORED_RESOURCE_H
