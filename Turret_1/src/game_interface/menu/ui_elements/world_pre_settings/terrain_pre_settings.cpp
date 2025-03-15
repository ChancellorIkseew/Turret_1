 
#include "terrain_pre_settings.h"

#include "map_structures/resources/res_enum.h"
#include "game_interface/ui_window/sub_win_util/fonts.h"
#include "map_structures/pre-settings/pre-settings.h"


TerrainPreSettingsPage::TerrainPreSettingsPage(const sf::Vector2i position) : Page(sf::Vector2i(700, 350), position)
{
	this->prepareInterfaceSprites();
	this->relocateWithOwner(sf::Vector2i(40, 60));
	isVisible = false;
}

void TerrainPreSettingsPage::prepareInterfaceSprites()
{
	const int line0 = 425;
	const int line1 = 445;
	const int line2 = 500;

	tFrequency = sf::Text(turretClassic, sf::String(L"Частота"), 12);
	tDepositSize= sf::Text(turretClassic, sf::String(L"Размер"), 12);
	tSeed = sf::Text(turretClassic, sf::String(L"Ключ генерации"), 12);
	tSmoothLayer = sf::Text(turretClassic, sf::String(L"Уровень сглаживания"), 12);
	tFrequency.setFillColor(standardColor);
	tDepositSize.setFillColor(standardColor);
	tSeed.setFillColor(standardColor);
	tSmoothLayer.setFillColor(standardColor);

	frequency[ResType::STONE] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 40));
	frequency[ResType::IRON] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 65));
	frequency[ResType::COPPER] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 90));
	frequency[ResType::SILICON] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 115));
	frequency[ResType::COAL] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 140));
	frequency[ResType::SULFUR] = TextField(sf::String(L"50"), 50, sf::Vector2i(line1, 165));

	depositSize[ResType::STONE] = TextField(sf::String(L"10"), 50, sf::Vector2i(line2, 40));
	depositSize[ResType::IRON] = TextField(sf::String(L"7"), 50, sf::Vector2i(line2, 65));
	depositSize[ResType::COPPER] = TextField(sf::String(L"5"), 50, sf::Vector2i(line2, 90));
	depositSize[ResType::SILICON] = TextField(sf::String(L"3"), 50, sf::Vector2i(line2, 115));
	depositSize[ResType::COAL] = TextField(sf::String(L"3"), 50, sf::Vector2i(line2, 140));
	depositSize[ResType::SULFUR] = TextField(sf::String(L"5"), 50, sf::Vector2i(line2, 165));

	resIco[ResType::STONE] = ResIco(ResType::STONE, sf::Vector2i(line0, 43));
	resIco[ResType::IRON] = ResIco(ResType::IRON, sf::Vector2i(line0, 68));
	resIco[ResType::COPPER] = ResIco(ResType::COPPER, sf::Vector2i(line0, 93));
	resIco[ResType::SILICON] = ResIco(ResType::SILICON, sf::Vector2i(line0, 118));
	resIco[ResType::COAL] = ResIco(ResType::COAL, sf::Vector2i(line0, 143));
	resIco[ResType::SULFUR] = ResIco(ResType::SULFUR, sf::Vector2i(line0, 168));

	seed = TextField(sf::String(L"0"), 90, sf::Vector2i(115, 40));
	smoothLayer = TextField(sf::String(L"0"), 18, sf::Vector2i(187, 65));
}

void TerrainPreSettingsPage::interact()
{
	if (!isVisible)
		return;
	for (auto& field : frequency)
		field.second.interact();
	for (auto& field : depositSize)
		field.second.interact();
	seed.interact();
	smoothLayer.interact();
}

void TerrainPreSettingsPage::enter(PreSettings& preSettings)
{
	std::map<ResType, int> iFrequency;
	std::map<ResType, int> iDepositSize;

	for (auto& [resType, field] : frequency)
		iFrequency[resType] = field.getValueUint32();
	for (auto& [resType, field] : depositSize)
		iDepositSize[resType] = field.getValueUint32();

	preSettings.changeTerrain().frequency = iFrequency;
	preSettings.changeTerrain().depositSize = iDepositSize;
	preSettings.changeTerrain().seed = seed.getValueUint32();
	preSettings.changeTerrain().smoothLayer = smoothLayer.getValueUint32();
}

void TerrainPreSettingsPage::relocateWithOwner(const sf::Vector2i ownerPosition)
{
	Page::relocateWithOwner(ownerPosition);
	tFrequency.setPosition(sf::Vector2f(position.x + 445, position.y + 20));
	tDepositSize.setPosition(sf::Vector2f(position.x + 500, position.y + 20));
	tSeed.setPosition(sf::Vector2f(position.x + 10, position.y + 43));
	tSmoothLayer.setPosition(sf::Vector2f(position.x + 10, position.y + 68));

	for (auto& field : frequency)
		field.second.relocateWithOwner(position);
	for (auto& field : depositSize)
		field.second.relocateWithOwner(position);
	for (auto& ico : resIco)
		ico.second.relocate(position);

	seed.relocateWithOwner(position);
	smoothLayer.relocateWithOwner(position);
}

void TerrainPreSettingsPage::draw(sf::RenderWindow& window)
{
	if (!isVisible)
		return;
	drawBase(window);
	window.draw(tFrequency);
	window.draw(tDepositSize);
	window.draw(tSeed);
	window.draw(tSmoothLayer);

	for (auto& field : depositSize)
		field.second.draw(window);
	for (auto& field : frequency)
		field.second.draw(window);
	for (auto& ico : resIco)
		ico.second.draw(window);

	seed.draw(window);
	smoothLayer.draw(window);
}
