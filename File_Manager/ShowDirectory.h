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

void ShowDirectory(Component* currentDir, const string& path)
{
	if (currentDir->Size() == 0)
	{
		for (const auto& object : fs::directory_iterator(path))
			if (fs::is_directory(object))
			{
				Component* subDir = new Directory(object.path().string());
				currentDir->Add(subDir);
			}
			else
			{
				Component* file = new File(object.path().string());
				currentDir->Add(file);
			}
		currentDir->Print();
	}
	else
		currentDir->Print();
}