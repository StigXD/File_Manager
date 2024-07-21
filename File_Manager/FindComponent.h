#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"


class Find : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	Find(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Поиск по названию";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string name;
		cout << "Поиск => " << endl;
		cin >> name;
		for (auto& findFile : fs::recursive_directory_iterator(currentPath))
			if (fs::is_regular_file(findFile))
				if (findFile.path().filename().string().find(name)!=-1)
					cout << format("Найден файл {}\n", findFile.path().string());
	}
};
