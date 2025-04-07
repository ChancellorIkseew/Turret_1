
#include "pre-settings.h"
#include <fstream>
#include <filesystem>

namespace stdfs = std::filesystem;
static const stdfs::path saves("saves");
static const stdfs::path preSettings("world_pre-settings.toml");

void PreSettings::save(const std::string& folder) const
{
    const stdfs::path path = saves / folder / preSettings;
    std::ofstream fout(path);
    if (!fout.is_open())
        throw std::runtime_error("Unable to open file to write: " + path.string());
    auto root = cpptoml::make_table();
    buildings.save(root);
    general.save(root);
    mobs.save(root);
    shells.save(root);
    terrain.save(root);
    timer.save(root);
    cpptoml::toml_writer writer(fout, " ");
    writer.visit(*root, false);
}

void PreSettings::load(const std::string& folder)
{
    const stdfs::path path = saves / folder / preSettings;
    const auto root = cpptoml::parse_file(path.string());
    buildings.load(root);
    general.load(root);
    mobs.load(root);
    shells.load(root);
    terrain.load(root);
    timer.load(root);
}
