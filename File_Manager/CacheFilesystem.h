#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>
#include <functional>

using namespace std;

namespace fs = filesystem;

void CacheFilesystem()
{
	string rootPath = fs::current_path().root_path().string();
	Component* LocalDrive = new Directory(rootPath);

	for (const auto& object : fs::directory_iterator(rootPath))
		if (fs::is_directory(object))
		{
			Component* subDir = new Directory(object.path().string());
			ShowDirectory(subDir, object.path().string());
			LocalDrive->Add(subDir);
		}
		else
		{
			Component* file = new File(object.path().string());
			LocalDrive->Add(file);
		}

}