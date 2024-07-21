#pragma once

#include "Component.h"
#include "ComponentFunction.h"
#include "Directory.h"
#include "File.h"

class Add : public IComponentFunction
{
	IComponent* currentDir;
	string currentPath;

public:
	Add(IComponent* currentDir, string& currentPath)
	{
		this->currentDir = currentDir;
		this->currentPath = currentPath;
	}

	string GetDescription() override
	{
		return "Создать директорию/файл";
	}

	void Run(IComponent*& currentDir, string& currentPath) override
	{
		string name;

		cout << "Введите название" << endl;

		getline(cin, name);

		fs::path newPath(currentPath);
		newPath.append(name);

		if(newPath.has_extension())
		{
			ofstream newFile;
			newFile.open(newPath.string());
			if (!newFile.is_open())
				cout << "Неудалось создать файл" << endl;
			else
			{
				IComponent* file = new File(newPath.string());
				currentDir->Add(file);
			}
			newFile.close();
		}
		else
		{
			IComponent* subDir = new Directory(newPath.string());
			if(fs::create_directory(newPath.string()))
				currentDir->Add(subDir);
			else
				cout << "Неудалось создать директорию" << endl;
		}
	}
};
