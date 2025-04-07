#pragma once
#ifndef T1_SYSTEM_FILES_H
#define T1_SYSTEM_FILES_H

#include <filesystem>

namespace t1::system
{
	namespace stdfs = std::filesystem;
	///@brief Create folder, if it does not exist.
	void tryCreateFolder(stdfs::path folder);
}

#endif // T1_SYSTEM_FILES_H
