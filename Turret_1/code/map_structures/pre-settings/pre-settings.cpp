
#include <fstream>
#include "util/parser/cpptoml.h"

#include "pre-settings.h"


PreSettings::PreSettings(std::string saveFolderName)
{
	
}


void PreSettings::save(const std::string& saveFolderName)
{
    const std::string saveFileName = "saves/" + saveFolderName + "/world_pre-settings.toml";
    std::ofstream fout;
    fout.open(saveFileName);
    if (!fout.is_open())
        throw std::runtime_error("Unable to open file to write: " + saveFileName);
    cpptoml::toml_writer writer(fout, " ");
    auto root = cpptoml::make_table();
    buildings.save(root);
    general.save(root);
    mobs.save(root);
    shells.save(root);
    terrain.save(root);
    timer.save(root);
    writer.visit(*root, false);
    fout.close();
}

void PreSettings::load(const std::string& saveFolderName)
{
    const std::string saveFileName = "saves/" + saveFolderName + "/world_pre-settings.toml";
    const auto root = std::move(cpptoml::parse_file(saveFileName));
    buildings.load(root);
    general.load(root);
    mobs.load(root);
    shells.load(root);
    terrain.load(root);
    timer.load(root);
}
