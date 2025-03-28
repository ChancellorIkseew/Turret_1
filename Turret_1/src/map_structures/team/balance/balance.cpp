
#include "balance.h"
#include "map_structures/pre-settings/pre-settings.h"
#include "map_structures/world/world.h"

constexpr uint64_t MAX_UINT32 = std::numeric_limits<uint32_t>::max();

Balance::Balance()
{
	balance = AllResources(0, 0, 0, 0, 0, 0);
}

void Balance::save(cereal::BinaryOutputArchive& archive) const {
	archive(balance);
}
void Balance::load(cereal::BinaryInputArchive& archive) {
	archive(balance);
}

void Balance::accept(const ResType type, const uint32_t amount)
{
	uint64_t sum = static_cast<uint64_t>(balance.allResources[type]) + static_cast<uint64_t>(amount);
	if (sum < MAX_UINT32)
		balance.allResources[type] += static_cast<uint32_t>(amount);
	else
		balance.allResources[type] = MAX_UINT32;
}

void Balance::giveStartRes(const std::map<ResType, uint32_t>& startRes)
{
	balance = startRes;
}

static uint32_t applyModifier(uint32_t price, float modifier) {
	return static_cast<uint32_t>(static_cast<float>(price) * modifier);
}

bool Balance::isEnough(const AllResources& expenses) const
{
	const float modifier = world->getPreSettings().getBuildings().expensesModifier;
	for (const auto& [res, amount] : expenses.allResources)
	{
		if (balance.allResources.find(res)->second < applyModifier(amount, modifier))
			return false;
	}
	return true;
}


void Balance::waste(const AllResources& expenses)
{
	const float modifier = world->getPreSettings().getBuildings().expensesModifier;
	for (auto& [res, amount] : expenses.allResources)
	{
		balance.allResources.find(res)->second -= applyModifier(amount, modifier);
	}
}
