
#include "files.h"

namespace stdfs = std::filesystem;

void t1::system::tryCreateFolder(stdfs::path folder)
{
	if (!stdfs::is_directory(folder))
		stdfs::create_directory(folder);
}

