
#include "buildings_info.h"
#include "buildings_enum.h"
#include "map_structures/base_engine/base_engine.h"

std::map<BuildingType, const BuildingInfo> BuildingsInfoTable::table
{
	std::pair<BuildingType, const BuildingInfo>

	{ BuildingType::REMOVE, { L"������ ������", 1, 0, {0, 0, 0, 0, 0, 0}, sf::IntRect({0, 0}, X1_RECT),
	L"������ ���������. �������, \n����������� �� ������������� \n��� ����� �� ������������."} },

	{ BuildingType::STONE_WALL, { L"�������� �����", 1, 100, {20, 0, 0, 0, 0, 0}, sf::IntRect({0, 480}, X1_RECT),
	L"�������� ������ ���������."} },
	{ BuildingType::STEEL_WALL, { L"�������� �����", 1, 300, {0, 32, 0, 0, 0, 0}, sf::IntRect({32, 480}, X1_RECT),
	L"�������� ������ ���������."} },

	//{ BuildingType::STONE_TOWER, { L"�������� �����", 1, 100, {20, 4, 0, 0, 0, 0}, sf::IntRect({0, 512}, X1_RECT),
	//L"��������� ��� ��������� \n�������.\n�������� ������ ���������."} },
	//{ BuildingType::STEEL_TOWER, { L"�������� �����", 1, 300, {0, 36, 0, 0, 0, 0}, sf::IntRect({32, 512}, X1_RECT),
	//L"��������� ��� ��������� \n�������.\n�������� ������ ���������."} },

	{ BuildingType::CORE_MK1, { L"���� mk1", 4, 1000, {400, 200, 300, 180, 0, 100}, sf::IntRect({64, 0}, X2_RECT),
	L"����. ����� ����."} },
	{ BuildingType::CORE_MK2, { L"���� mk2", 16, 4000, {1600, 800, 1200, 720, 0, 400}, sf::IntRect({0, 64}, X4_RECT),
	L"����. ����� ����."} },
	{ BuildingType::CORE_MK3, { L"���� mk3", 16, 4000, {1600, 800, 1200, 720, 0, 400}, sf::IntRect({0, 128}, X6_RECT),
	L"����. ����� ����."} },


	{ BuildingType::STANDARD_CONVEYER, { L"��������", 1, 15, {1, 2, 1, 0, 0, 0}, sf::IntRect({0, 192}, X1_RECT),
	L"���������� ������� ����� \n�����������. \n����� ��������� ��������, \n������� ���."} },
	{ BuildingType::SHIELDED_CONVEYER, { L"�������������� ��������", 1, 30, {2, 4, 1, 0, 0, 0}, sf::IntRect({32, 192}, X1_RECT),
	L"���������� ������� ����� \n�����������. ���������\n �������� �� ����� ������ �� \n����������. ����� ���������\n ��������, ������� ���."} },
	 
	{ BuildingType::BRIDGE, { L"����", 1, 15, {2, 5, 2, 0, 0, 0}, sf::IntRect({128, 544}, X1_RECT),
	L"������� ������� \n���������� �������������� \n� ��������� �����������. \n����� ��������� ����, \n������� ���."} },
	{ BuildingType::ROUTER, { L"�������������", 1, 15, {2, 3, 2, 1, 0, 0}, sf::IntRect({128, 512}, X1_RECT),
	L"��������� ������� � ����� \n������� � ������������ \n�� ���������� ���� \n��������� ����������."} },
	{ BuildingType::INTERSECTION, { L"����������", 1, 15, {2, 3, 2, 0, 0, 0}, sf::IntRect({128, 480}, X1_RECT),
	L"��������� ���� ���������� \n��������������� �������� \n���� �����."} },
	{ BuildingType::SORTER, { L"�����������", 1, 15, {2, 3, 2, 2, 0, 0}, sf::IntRect({160, 480}, X1_RECT),
	L"(�������� ������� �� ����, \n��� ��������� ������� �����)"} },
	 
	{ BuildingType::SMALL_DRILL, { L"����� ���", 1, 70, {10, 14, 8, 0, 0, 0}, sf::IntRect({0, 224}, X1_RECT),
	L"�������� ������ �� ������, \n� ������� ����������. \n�� ������� ������� ��� \n������."} },
	{ BuildingType::BIG_DRILL, { L"������� ���", 4, 320, {40, 56, 32, 8, 0, 0}, sf::IntRect({0, 256}, X2_RECT),
	L"�������� ������� �� ������, \n� ������� ����������. \n������� 10 ��. ������� � \n������� ��� ������."} },
	{ BuildingType::EFFECTIVE_DRILL, { L"����������� ���", 9, 800, {90, 126, 72, 18, 0, 0}, sf::IntRect({64, 224}, X3_RECT),
	L"�������� ������� �� ������, \n� ������� ����������. \n������� 20 ��. ������� � \n������� ��� ������."} },
	{ BuildingType::REINFORCED_DRILL, { L"��������� ���", 1, 90, {10, 14, 8, 4, 0, 0}, sf::IntRect({32, 224}, X1_RECT),
	L"�������� ������� �� ������, \n� ������� ����������. \n�������� �������� ���� � ��������. \n������� 10 ��. ������� � \n������� ��� ������."} },

	{ BuildingType::SHELL_FACTORY, { L"����� ��������", 4, 400, {60, 80, 32, 24, 0, 0}, sf::IntRect({0, 320}, X2_RECT),
	L"���������� ������� ��� \n���������."} },
	{ BuildingType::ROCKET_FACTORY, { L"����� �����", 9, 800, {160, 240, 100, 90, 0, 0}, sf::IntRect({0, 384}, X3_RECT),
	L"���������� ������."} },

	{ BuildingType::AUTOCANNON_TURRET, { L"������������ ������", 1, 0, {20, 16, 6, 2, 0, 0}, sf::IntRect({0, 544}, X1_RECT),
	L"�������� ��������� \n��������� � ������� \n�����������������."} },
	{ BuildingType::ROCKET_TURRET, { L"�������� ������", 1, 0, {20, 14, 6, 5, 0, 0}, sf::IntRect({32, 544}, X1_RECT),
	L"�������� �������� � \n������� �������� \n������."} },

	{ BuildingType::COAL_GENERATOR, { L"���������", 1, 15, {5, 10, 5, 0, 0, 0}, sf::IntRect({0, 0}, X2_RECT),
	L"������������ ������� \n(�������� ������� �� ����, \n��� ��������� ������� �����)"} },
};

const BuildingInfo BuildingsInfoTable::at(const BuildingType type)
{
	return table[type];
}

bool BuildingsInfoTable::exists(const BuildingType type)
{
	return table.contains(type);
}

void BuildingsInfoTable::addBuildingsInfo(const BuildingType type, const BuildingInfo info)
{

}
