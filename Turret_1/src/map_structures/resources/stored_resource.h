#pragma once
#ifndef STORED_RESOURCE_H
#define STORED_RESOURCE_H

#include "res_enum.h"
#include <typeinfo>
#include <cereal/archives/binary.hpp>

struct StoredResource
{
	StoredResource() = default;
	StoredResource(ResType type, uint16_t quantity) :
		type(type), quantity(quantity) { }

	void save(cereal::BinaryOutputArchive& archive) const {
		archive(type, quantity);
	}
	void load(cereal::BinaryInputArchive& archive) {
		archive(type, quantity);
	}

	ResType type = ResType::NO_RESOURCES;
	uint16_t quantity = 0;
};

#endif // STORED_RESOURCE_H
