#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <windows.h>
#include <format>
#include <functional>
#include "ShowDirectory.h"
#include "Component.h"
#include "Menu.h"


using namespace std;

namespace fs = filesystem;


class IFileManager
{
public:
	virtual ~IFileManager() = default;

	virtual void OpenDir() = 0;
	virtual void Create() = 0;
	virtual void Remove() = 0;
	virtual void Copy() = 0;
	virtual void GetSize() = 0;
	virtual void Find() = 0;

};

class FileManager :public IFileManager
{

};
